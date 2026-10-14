// cube.cpp : exercice 21, « Un cube, et rien d'autre »
// Affiche un seul cube blanc, à deux mètres devant la caméra, éclairé par un soleil.
// Mettre PROVOQUER_CAUSE à 1 retire la boîte englobante (aabb) du cube : l'écran reste alors vide.

// --- Plateforme, fenêtre, événements, journal ---
#include "NKPlatform/NkPlatformDetect.h"
#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKLogger/NkLog.h"

// --- Couche basse (NKRHI : le périphérique) et couche haute (NKRenderer) ---
#include "NKRHI/Core/NkDeviceFactory.h"
#include "NKRenderer/NkRenderer.h"
#include "NKRenderer/Core/NkCamera.h"
#include "NKRenderer/Mesh/NkMeshSystem.h"
#include "NKRenderer/Tools/Render3D/NkRender3D.h"

#include <cmath>

using namespace nkentseu;
using namespace nkentseu::renderer;

// 0 : le cube porte sa boîte englobante, il s'affiche.
// 1 : la boîte englobante n'est pas renseignée, le renderer écarte le cube en silence.
#define PROVOQUER_CAUSE 0

// Nom de l'application, enregistré auprès du point d'entrée du moteur.
static void ConfigureAppData(NkAppData &d) {
	d.appName = "Cube";
}
NK_REGISTER_ENTRY_APPDATA_UPDATER(ConfigureAppData)

int nkmain(const NkEntryState &state) {
	(void)state;

	// ---------- 1. Fenêtre ----------
	NkWindowConfig winCfg;
	winCfg.title = "Un cube, et rien d'autre";
	winCfg.width = 1280;
	winCfg.height = 720;
	winCfg.centered = true;
	winCfg.resizable = true;

	NkWindow window(winCfg);
	if (!window.IsValid()) {
		logger.Error("[Cube] Creation fenetre KO");
		return 1;
	}

	// ---------- 2. Périphérique ----------
	// La fenêtre décrit, dans un objet neutre, sur quoi la carte graphique devra dessiner.
	NkDeviceInitInfo devInfo{};
	devInfo.surface = window.GetSurfaceDesc();
	devInfo.width = (uint32)window.GetSize().width;
	devInfo.height = (uint32)window.GetSize().height;

	// La détection automatique choisit l'interface graphique (Vulkan, OpenGL, logiciel...).
	NkIDevice *device = NkDeviceFactory::CreateAutoDetect(devInfo);
	if (!device || !device->IsValid()) {
		logger.Error("[Cube] Creation device KO");
		window.Close();
		return 2;
	}
	// On affiche l'interface retenue : utile si la scène est lente sur une autre machine.
	logger.Info("[Cube] Backend : {0}", NkGraphicsApiName(device->GetApi()));

	// ---------- 3. Renderer ----------
	NkRendererConfig cfg = NkRendererConfig::ForGame(devInfo.api, devInfo.width, devInfo.height);
	// On nomme les sous-systèmes voulus : seul le dessin de maillages 3D, pas tout par défaut.
	cfg.subsystems = NK_SS_RENDER3D;
	NkRenderer *renderer = NkRenderer::Create(device, cfg);
	if (!renderer || !renderer->Initialize()) {
		logger.Error("[Cube] Init renderer KO");
		NkRenderer::Destroy(renderer);
		NkDeviceFactory::Destroy(device);
		window.Close();
		return 3;
	}
	// Outil de dessin 3D du renderer, et cube unitaire du système de maillages
	// (il va de -0,5 à +0,5 sur chaque axe, centré à l'origine).
	NkRender3D *r3d = renderer->GetRender3D();
	NkMeshHandle meshCube = renderer->GetMeshSystem()->GetCube();

	// ---------- 4. Événements : fermeture, Échap, redimensionnement ----------
	bool running = true;
	uint32 W = devInfo.width;
	uint32 H = devInfo.height;
	NkEventSystem &events = NkEvents();
	events.AddEventCallback<NkWindowCloseEvent>([&](NkWindowCloseEvent *) { running = false; });
	events.AddEventCallback<NkKeyPressEvent>([&](NkKeyPressEvent *e) {
		if (e->GetKey() == NkKey::NK_ESCAPE)
			running = false;
	});
	events.AddEventCallback<NkWindowResizeEvent>([&](NkWindowResizeEvent *e) {
		const uint32 w = (uint32)e->GetWidth(), h = (uint32)e->GetHeight();
		if (w > 0 && h > 0 && (w != W || h != H)) {
			W = w;
			H = h;
			renderer->OnResize(w, h);
		}
	});

	// ---------- 5. Caméra : debout, près de l'entrée ----------
	const NkVec3f pos{0.f, 1.70f, 1.5f};    // hauteur des yeux : 1,70 m
	const NkVec3f cible{0.f, 1.40f, -2.f};  // point regardé

	// ---------- 6. Place du cube : 2 m devant la caméra, sur son axe de visée ----------
	// Vecteur caméra -> cible, puis sa longueur pour le normaliser.
	const float32 dx = cible.x - pos.x;
	const float32 dy = cible.y - pos.y;
	const float32 dz = cible.z - pos.z;
	const float32 longueur = std::sqrt(dx * dx + dy * dy + dz * dz);
	const float32 DISTANCE = 2.0f;  // deux mètres
	// Centre du cube = position de la caméra + 2 m dans la direction de la cible.
	const NkVec3f centre{pos.x + dx / longueur * DISTANCE, pos.y + dy / longueur * DISTANCE,
						 pos.z + dz / longueur * DISTANCE};
	// Échelle appliquée au cube unitaire : arête de 0,5 m.
	const NkVec3f taille{0.5f, 0.5f, 0.5f};

	// ---------- 7. Boucle de rendu ----------
	while (running && window.IsOpen()) {
		events.PollEvents();
		if (!running)
			break;
		// Préparer l'image ; si elle n'est pas disponible, on passe à la suivante.
		if (!renderer->BeginFrame())
			continue;

		// Caméra de la scène : haut, champ vertical 70 degrés, plans rapproché 0,05 et éloigné 200.
		NkCamera3DData camData;
		camData.up = {0.f, 1.f, 0.f};
		camData.fovY = 70.f;
		camData.aspect = (float32)W / (float32)H;
		camData.nearPlane = 0.05f;
		camData.farPlane = 200.f;
		NkCamera3D cam(camData);
		cam.SetPosition(pos);
		cam.SetTarget(cible);

		// Contexte de scène : la caméra et les lumières, donnés au début de chaque image.
		NkSceneContext sctx;
		sctx.camera = cam;

		// Soleil : lumière directionnelle.
		NkLightDesc soleil;
		soleil.type = NkLightType::NK_DIRECTIONAL;
		soleil.direction = {-0.4f, -1.f, -0.3f};
		soleil.color = {1.f, 0.95f, 0.85f};
		soleil.intensity = 3.f;
		soleil.castShadow = false;  // pas d'ombre nécessaire pour un seul cube
		sctx.lights.PushBack(soleil);

		// Poser la scène.
		r3d->BeginScene(sctx);

		// Soumettre le cube : maillage, transformation, teinte et boîte englobante.
		NkDrawCall3D d;
		d.mesh = meshCube;
		// Lue de droite à gauche : d'abord l'échelle, ensuite la translation vers le centre.
		d.transform = NkMat4f::Translate(centre) * NkMat4f::Scale(taille);
		d.tint = {1.f, 1.f, 1.f};  // blanc
#if !PROVOQUER_CAUSE
		// Boîte englobante en COORDONNÉES DU MONDE : suit la place et la taille du cube,
		// pas celles du cube unitaire. Le renderer décide de ce qui est visible d'après elle.
		d.aabb.min = {centre.x - taille.x * 0.5f, centre.y - taille.y * 0.5f, centre.z - taille.z * 0.5f};
		d.aabb.max = {centre.x + taille.x * 0.5f, centre.y + taille.y * 0.5f, centre.z + taille.z * 0.5f};
#endif
		// Soumettre n'est pas dessiner : l'ordre est seulement enregistré.
		// Sans aabb, Submit ne dit rien et l'objet est écarté en silence.
		r3d->Submit(d);

		// TODO : le cours décrit une étape « exécuter » entre la soumission et la présentation.
		// Si ton exemple de cours appelle r3d->EndScene() (ou un équivalent), ajoute-le ici.

		// Présenter l'image à l'écran, puis la terminer.
		renderer->Present();
		renderer->EndFrame();
	}

	// ---------- 8. Nettoyage : attendre la carte, puis détruire dans l'ordre inverse ----------
	device->WaitIdle();
	NkRenderer::Destroy(renderer);
	NkDeviceFactory::Destroy(device);
	window.Close();
	return 0;
}
