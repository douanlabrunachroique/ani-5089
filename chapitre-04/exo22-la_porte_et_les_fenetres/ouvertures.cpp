// ouvertures.cpp : exercice 22
// Une porte et deux fenêtres dans une salle 3D.

#include "NKPlatform/NkPlatformDetect.h"
#include "NKWindow/NKMain.h"
#include "NKWindow/Core/NkWindow.h"
#include "NKWindow/Core/NkWindowConfig.h"
#include "NKEvent/NkWindowEvent.h"
#include "NKEvent/NkKeyboardEvent.h"
#include "NKLogger/NkLog.h"

#include "NKRHI/Core/NkDeviceFactory.h"
#include "NKRenderer/NkRenderer.h"
#include "NKRenderer/Core/NkCamera.h"
#include "NKRenderer/Mesh/NkMeshSystem.h"
#include "NKRenderer/Tools/Render3D/NkRender3D.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

static void ConfigureAppData(NkAppData &d) {
    d.appName = "Ouvertures";
}

NK_REGISTER_ENTRY_APPDATA_UPDATER(ConfigureAppData)

int nkmain(const NkEntryState &state) {
    (void)state;

    // 1. Fenetre
    NkWindowConfig winCfg;
    winCfg.title = "Exercice 22 - Porte et fenetres";
    winCfg.width = 1280;
    winCfg.height = 720;
    winCfg.centered = true;
    winCfg.resizable = true;

    NkWindow window(winCfg);

    if (!window.IsValid()) {
        logger.Error("[Ouvertures] Creation fenetre KO");
        return 1;
    }

    // 2. Peripherique graphique
    NkDeviceInitInfo devInfo{};
    devInfo.surface = window.GetSurfaceDesc();
    devInfo.width = (uint32)window.GetSize().width;
    devInfo.height = (uint32)window.GetSize().height;

    NkIDevice *device = NkDeviceFactory::CreateAutoDetect(devInfo);

    if (!device || !device->IsValid()) {
        logger.Error("[Ouvertures] Creation device KO");
        NkDeviceFactory::Destroy(device);
        window.Close();
        return 2;
    }

    // 3. Renderer
    NkRendererConfig cfg =
        NkRendererConfig::ForGame(devInfo.api, devInfo.width, devInfo.height);

    cfg.subsystems = NK_SS_RENDER3D;

    NkRenderer *renderer = NkRenderer::Create(device, cfg);

    if (!renderer || !renderer->Initialize()) {
        logger.Error("[Ouvertures] Initialisation renderer KO");
        NkRenderer::Destroy(renderer);
        NkDeviceFactory::Destroy(device);
        window.Close();
        return 3;
    }

    NkRender3D *r3d = renderer->GetRender3D();
    NkMeshHandle cube = renderer->GetMeshSystem()->GetCube();

    // 4. Dimensions de la salle
    const float32 largeurSalle = 4.0f;
    const float32 profondeurSalle = 4.0f;
    const float32 hauteurSalle = 2.50f;
    const float32 epaisseurMur = 0.10f;

    // Les faces interieures des murs sont a x = -1.90 et z = -1.90.
    const float32 faceInterieureGauche =
        -largeurSalle / 2.0f + epaisseurMur;

    const float32 faceInterieureFond =
        -profondeurSalle / 2.0f + epaisseurMur;

    // Decalage des panneaux vers l'interieur pour eviter le z-fighting.
    const float32 decalage = 0.01f;

    // 5. Porte : largeur 0.90 m, hauteur 2.00 m.
    const float32 largeurPorte = 0.90f;
    const float32 hauteurPorte = 2.00f;
    const float32 epaisseurPanneau = 0.02f;

    const float32 xPorte = -0.70f;
    const float32 yPorte = hauteurPorte / 2.0f;
    const float32 zPorte =
        faceInterieureFond + epaisseurPanneau / 2.0f + decalage;

    // 6. Fenetres : largeur 1.20 m, hauteur 1.00 m.
    const float32 largeurFenetre = 1.20f;
    const float32 hauteurFenetre = 1.00f;
    const float32 yFenetre = 1.40f;

    const float32 zFenetre1 = -0.90f;
    const float32 zFenetre2 = 0.90f;

    const float32 xFenetre =
        faceInterieureGauche + epaisseurPanneau / 2.0f + decalage;

    // 7. Camera
    const NkVec3f posCamera{0.0f, 1.60f, 1.70f};
    const NkVec3f cibleCamera{0.0f, 1.30f, -1.50f};

    // 8. Evenements
    bool running = true;
    uint32 W = devInfo.width;
    uint32 H = devInfo.height;

    NkEventSystem &events = NkEvents();

    events.AddEventCallback<NkWindowCloseEvent>(
        [&](NkWindowCloseEvent *) {
            running = false;
        }
    );

    events.AddEventCallback<NkKeyPressEvent>(
        [&](NkKeyPressEvent *e) {
            if (e->GetKey() == NkKey::NK_ESCAPE)
                running = false;
        }
    );

    events.AddEventCallback<NkWindowResizeEvent>(
        [&](NkWindowResizeEvent *e) {
            uint32 w = (uint32)e->GetWidth();
            uint32 h = (uint32)e->GetHeight();

            if (w > 0 && h > 0 && (w != W || h != H)) {
                W = w;
                H = h;
                renderer->OnResize(w, h);
            }
        }
    );

    // 9. Boucle de rendu
    while (running && window.IsOpen()) {
        events.PollEvents();

        if (!running)
            break;

        if (!renderer->BeginFrame())
            continue;

        NkCamera3DData camData;
        camData.up = {0.f, 1.f, 0.f};
        camData.fovY = 70.f;
        camData.aspect = (float32)W / (float32)H;
        camData.nearPlane = 0.05f;
        camData.farPlane = 200.f;

        NkCamera3D cam(camData);
        cam.SetPosition(posCamera);
        cam.SetTarget(cibleCamera);

        NkSceneContext sctx;
        sctx.camera = cam;

        NkLightDesc soleil;
        soleil.type = NkLightType::NK_DIRECTIONAL;
        soleil.direction = {-0.4f, -1.f, -0.3f};
        soleil.color = {1.f, 0.95f, 0.85f};
        soleil.intensity = 3.f;
        soleil.castShadow = false;

        sctx.lights.PushBack(soleil);

        r3d->BeginScene(sctx);

        // Fonction de dessin d'un panneau rectangulaire.
        auto dessinerPanneau = [&](const NkVec3f &centre,
                                   const NkVec3f &taille,
                                   const NkVec3f &couleur) {
            NkDrawCall3D d;
            d.mesh = cube;

            d.transform =
                NkMat4f::Translate(centre) *
                NkMat4f::Scale(taille);

            d.tint = couleur;

            d.aabb.min = {
                centre.x - taille.x / 2.0f,
                centre.y - taille.y / 2.0f,
                centre.z - taille.z / 2.0f
            };

            d.aabb.max = {
                centre.x + taille.x / 2.0f,
                centre.y + taille.y / 2.0f,
                centre.z + taille.z / 2.0f
            };

            r3d->Submit(d);
        };

        // Porte sur le mur du fond.
        dessinerPanneau(
            {xPorte, yPorte, zPorte},
            {largeurPorte, hauteurPorte, epaisseurPanneau},
            {0.35f, 0.15f, 0.08f}
        );

        // Fenetre 1 sur le mur gauche.
        dessinerPanneau(
            {xFenetre, yFenetre, zFenetre1},
            {epaisseurPanneau, hauteurFenetre, largeurFenetre},
            {0.20f, 0.65f, 0.90f}
        );

        // Fenetre 2 sur le mur gauche.
        dessinerPanneau(
            {xFenetre, yFenetre, zFenetre2},
            {epaisseurPanneau, hauteurFenetre, largeurFenetre},
            {0.20f, 0.65f, 0.90f}
        );

        // Ajouter les murs de la salle ici si le code de l'exercice
        // precedent est disponible.

        renderer->Present();
        renderer->EndFrame();
    }

    // 10. Nettoyage
    device->WaitIdle();

    NkRenderer::Destroy(renderer);
    NkDeviceFactory::Destroy(device);

    window.Close();

    return 0;
}
