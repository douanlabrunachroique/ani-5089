

#include <iostream>

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
#include "NKImage/Core/NkImage.h"
#include "NKRenderer/Materials/NkMaterial.h"

using namespace nkentseu;
using namespace nkentseu::renderer;

static const float INTERIEUR = 4.0f;
static const float HAUTEUR = 2.50f;
static const float EP_MUR = 0.10f;
static const float AVANCE = 0.002f;

static void ConfigureAppData(NkAppData &d) {
    d.appName = "Inexistant";
}

NK_REGISTER_ENTRY_APPDATA_UPDATER(ConfigureAppData)

// Test de chargement : cinq lignes au maximum.
static void TesterImage() {
    NkImage image;
    bool charge = image.Load("murs/nexistepas.png");
    std::cout << "charge : " << charge << ", valide : " << image.IsValid()
              << ", largeur : " << image.Width()
              << ", hauteur : " << image.Height() << std::endl;
}

static NkMat4f PoserAuSol(NkVec3f taille, float x, float z) {
    return NkMat4f::Translate({x, taille.y * 0.5f, z})
         * NkMat4f::Scale(taille);
}

static void Soumettre(
    NkRender3D *r3d,
    NkMeshHandle cube,
    const NkMat4f &m,
    NkVec3f couleur
) {
    NkDrawCall3D d;
    d.mesh = cube;
    d.transform = m;
    d.tint = couleur;
    d.metallic = 0.f;
    d.roughness = 0.9f;
    d.aabb = NkAABB::Unit().Transformed(m);
    r3d->Submit(d);
}

static void ConstruireSalle(NkRender3D *r3d, NkMeshHandle cube) {
    const NkVec3f mur{0.72f, 0.70f, 0.66f};
    const NkVec3f sol{0.35f, 0.33f, 0.30f};
    const NkVec3f porte{0.45f, 0.28f, 0.15f};
    const NkVec3f fenetre{0.55f, 0.75f, 0.90f};
    const NkVec3f bois{0.62f, 0.42f, 0.22f};
    const float large = INTERIEUR + 2.f * EP_MUR;
    const float murZ = -(INTERIEUR * 0.5f + EP_MUR * 0.5f);
    const float faceZ = murZ + EP_MUR * 0.5f;
    const float faceX = -(INTERIEUR * 0.5f);

    // Murs de la salle.
    Soumettre(r3d, cube,
        PoserAuSol({large, HAUTEUR, EP_MUR}, 0.f, murZ), mur);
    Soumettre(r3d, cube,
        PoserAuSol({large, HAUTEUR, EP_MUR}, 0.f, -murZ), mur);
    Soumettre(r3d, cube,
        PoserAuSol({EP_MUR, HAUTEUR, INTERIEUR}, murZ, 0.f), mur);
    Soumettre(r3d, cube,
        PoserAuSol({EP_MUR, HAUTEUR, INTERIEUR}, -murZ, 0.f), mur);

    // Porte décorative.
    Soumettre(r3d, cube,
        PoserAuSol({0.90f, 2.00f, 0.02f},
                   -0.70f, faceZ - 0.01f + AVANCE), porte);

    // Sol et plafond.
    Soumettre(r3d, cube,
        NkMat4f::Translate({0.f, -EP_MUR * 0.5f, 0.f})
        * NkMat4f::Scale({large, EP_MUR, large}), sol);

    Soumettre(r3d, cube,
        NkMat4f::Translate({0.f, HAUTEUR + EP_MUR * 0.5f, 0.f})
        * NkMat4f::Scale({large, EP_MUR, large}), mur);

    // Fenêtres décoratives.
    const float fenetreX = faceX - 0.01f + AVANCE;

    Soumettre(r3d, cube,
        NkMat4f::Translate({fenetreX, 1.40f, -0.90f})
        * NkMat4f::Scale({0.02f, 1.00f, 1.20f}), fenetre);

    Soumettre(r3d, cube,
        NkMat4f::Translate({fenetreX, 1.40f, 0.90f})
        * NkMat4f::Scale({0.02f, 1.00f, 1.20f}), fenetre);

    // Table décorative.
    Soumettre(r3d, cube,
        NkMat4f::Translate({0.60f, 0.725f, 0.70f})
        * NkMat4f::Scale({1.20f, 0.05f, 0.80f}), bois);
}

// Applique le matériau de la texture inexistante à un mur.
static void ConstruireMurTexture(
    NkRender3D *r3d,
    NkMeshHandle cube,
    NkMaterial *mat
) {
    const float large = INTERIEUR + 2.f * EP_MUR;
    const float murZ = -(INTERIEUR * 0.5f + EP_MUR * 0.5f);

    NkMat4f m = PoserAuSol(
        {large, HAUTEUR, EP_MUR},
        0.f,
        murZ
    );

    NkDrawCall3D dc;
    dc.mesh = cube;
    dc.transform = m;
    dc.material = mat->GetInstHandle();
    dc.tint = {1.f, 1.f, 1.f};
    dc.metallic = 0.f;
    dc.roughness = 0.9f;
    dc.aabb = NkAABB::Unit().Transformed(m);

    r3d->Submit(dc);
}

int nkmain(const NkEntryState &state) {
    (void)state;

    // Première tentative : chargement avec NkImage.
    TesterImage();

    NkWindowConfig winCfg;
    winCfg.title = "Image inexistante";
    winCfg.width = 1280;
    winCfg.height = 720;
    winCfg.centered = true;
    winCfg.resizable = true;

    NkWindow window(winCfg);

    if (!window.IsValid()) {
        logger.Error("[Inexistant] Creation fenetre KO");
        return 1;
    }

    NkDeviceInitInfo devInfo{};
    devInfo.surface = window.GetSurfaceDesc();
    devInfo.width = (uint32)window.GetSize().width;
    devInfo.height = (uint32)window.GetSize().height;

    NkIDevice *device = NkDeviceFactory::CreateAutoDetect(devInfo);

    if (!device || !device->IsValid()) {
        logger.Error("[Inexistant] Creation device KO");
        window.Close();
        return 2;
    }

    logger.Info(
        "[Inexistant] Backend : {0}",
        NkGraphicsApiName(device->GetApi())
    );

    NkRendererConfig cfg = NkRendererConfig::ForGame(
        devInfo.api,
        devInfo.width,
        devInfo.height
    );

    cfg.subsystems = NK_SS_RENDER3D;

    NkRenderer *renderer = NkRenderer::Create(device, cfg);

    if (!renderer || !renderer->Initialize()) {
        logger.Error("[Inexistant] Init renderer KO");
        NkRenderer::Destroy(renderer);
        NkDeviceFactory::Destroy(device);
        window.Close();
        return 3;
    }

    NkRender3D *r3d = renderer->GetRender3D();
    NkMeshHandle cube = renderer->GetMeshSystem()->GetCube();

    // Deuxième tentative : charger la texture inexistante.
    const char *chemin = "murs/nexistepas.png";

    logger.Info(
        "[Inexistant] Tentative de chargement du fichier : {0}",
        chemin
    );

    auto texture = renderer->GetTextures()->Load(chemin);

    NkMaterial *mat = NkMaterial::Create(
        renderer->GetMaterials(),
        NkMaterialType::NK_PBR_METALLIC
    );

    if (mat) {
        mat->SetAlbedoMap(texture);
    } else {
        logger.Error("[Inexistant] Creation du materiau KO");
    }

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
            if (e->GetKey() == NkKey::NK_ESCAPE) {
                running = false;
            }
        }
    );

    events.AddEventCallback<NkWindowResizeEvent>(
        [&](NkWindowResizeEvent *e) {
            const uint32 w = (uint32)e->GetWidth();
            const uint32 h = (uint32)e->GetHeight();

            if (w > 0 && h > 0 && (w != W || h != H)) {
                W = w;
                H = h;
                renderer->OnResize(w, h);
            }
        }
    );

    const NkVec3f pos{1.5f, 1.5f, 1.7f};
    const NkVec3f cible{-0.3f, 0.8f, -0.3f};

    while (running && window.IsOpen()) {
        events.PollEvents();

        if (!running) {
            break;
        }

        if (!renderer->BeginFrame()) {
            continue;
        }

        NkCamera3DData camData;
        camData.up = {0.f, 1.f, 0.f};
        camData.fovY = 70.f;
        camData.aspect = (float32)W / (float32)H;
        camData.nearPlane = 0.05f;
        camData.farPlane = 200.f;

        NkCamera3D cam(camData);
        cam.SetPosition(pos);
        cam.SetTarget(cible);

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

        ConstruireSalle(r3d, cube);

        if (mat) {
            ConstruireMurTexture(r3d, cube, mat);
        }

        renderer->Present();
        renderer->EndFrame();
    }

    device->WaitIdle();

    NkRenderer::Destroy(renderer);
    NkDeviceFactory::Destroy(device);
    window.Close();

    return 0;
}

