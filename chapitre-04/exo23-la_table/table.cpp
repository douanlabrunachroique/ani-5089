// table.cpp : exercice 23, « La table »
// Une table avec un plateau et quatre pieds, posée sur le sol.

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
    d.appName = "Table";
}

NK_REGISTER_ENTRY_APPDATA_UPDATER(ConfigureAppData)

int nkmain(const NkEntryState &state) {
    (void)state;

    // 1. Fenetre
    NkWindowConfig winCfg;
    winCfg.title = "Exercice 23 - La table";
    winCfg.width = 1280;
    winCfg.height = 720;
    winCfg.centered = true;
    winCfg.resizable = true;

    NkWindow window(winCfg);

    if (!window.IsValid()) {
        logger.Error("[Table] Creation fenetre KO");
        return 1;
    }

    // 2. Peripherique graphique
    NkDeviceInitInfo devInfo{};
    devInfo.surface = window.GetSurfaceDesc();
    devInfo.width = (uint32)window.GetSize().width;
    devInfo.height = (uint32)window.GetSize().height;

    NkIDevice *device = NkDeviceFactory::CreateAutoDetect(devInfo);

    if (!device || !device->IsValid()) {
        logger.Error("[Table] Creation device KO");
        NkDeviceFactory::Destroy(device);
        window.Close();
        return 2;
    }

    // 3. Renderer : dessin de maillages 3D
    NkRendererConfig cfg =
        NkRendererConfig::ForGame(devInfo.api, devInfo.width, devInfo.height);

    cfg.subsystems = NK_SS_RENDER3D;

    NkRenderer *renderer = NkRenderer::Create(device, cfg);

    if (!renderer || !renderer->Initialize()) {
        logger.Error("[Table] Initialisation renderer KO");
        NkRenderer::Destroy(renderer);
        NkDeviceFactory::Destroy(device);
        window.Close();
        return 3;
    }

    NkRender3D *r3d = renderer->GetRender3D();
    NkMeshHandle cube = renderer->GetMeshSystem()->GetCube();

    // 4. Evenements
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

    // 5. Dimensions de la table, en metres
    const float32 longueur = 1.20f;
    const float32 profondeur = 0.80f;
    const float32 epaisseur = 0.05f;

    const float32 sectionPied = 0.06f;
    const float32 hauteurDessus = 0.75f;

    // Centre horizontal impose par l'enonce
    const float32 centreX = 0.60f;
    const float32 centreZ = 0.70f;

    // 6. Calculs verticaux
    const float32 yPlateau = hauteurDessus - epaisseur / 2.0f;
    const float32 hauteurPied = hauteurDessus - epaisseur;
    const float32 yPied = hauteurPied / 2.0f;

    // 7. Positions des quatre pieds
    const float32 xGauche =
        centreX - longueur / 2.0f + sectionPied / 2.0f;

    const float32 xDroite =
        centreX + longueur / 2.0f - sectionPied / 2.0f;

    const float32 zAvant =
        centreZ - profondeur / 2.0f + sectionPied / 2.0f;

    const float32 zArriere =
        centreZ + profondeur / 2.0f - sectionPied / 2.0f;

    // 8. Camera
    const NkVec3f posCamera{1.80f, 1.60f, 2.60f};
    const NkVec3f cibleCamera{0.60f, 0.35f, 0.70f};

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

        // Lumiere directionnelle
        NkLightDesc soleil;
        soleil.type = NkLightType::NK_DIRECTIONAL;
        soleil.direction = {-0.4f, -1.f, -0.3f};
        soleil.color = {1.f, 0.95f, 0.85f};
        soleil.intensity = 3.f;
        soleil.castShadow = false;

        sctx.lights.PushBack(soleil);

        r3d->BeginScene(sctx);

        // 10. Plateau
        NkDrawCall3D plateau;
        plateau.mesh = cube;

        const NkVec3f taillePlateau{
            longueur,
            epaisseur,
            profondeur
        };

        const NkVec3f centrePlateau{
            centreX,
            yPlateau,
            centreZ
        };

        plateau.transform =
            NkMat4f::Translate(centrePlateau) *
            NkMat4f::Scale(taillePlateau);

        plateau.tint = {0.55f, 0.30f, 0.15f};

        plateau.aabb.min = {
            centreX - longueur / 2.0f,
            yPlateau - epaisseur / 2.0f,
            centreZ - profondeur / 2.0f
        };

        plateau.aabb.max = {
            centreX + longueur / 2.0f,
            yPlateau + epaisseur / 2.0f,
            centreZ + profondeur / 2.0f
        };

        r3d->Submit(plateau);

        // 11. Dimensions communes des quatre pieds
        const NkVec3f taillePied{
            sectionPied,
            hauteurPied,
            sectionPied
        };

        // Fonction de preparation d'un pied
        auto dessinerPied = [&](float32 x, float32 z) {
            NkDrawCall3D pied;
            pied.mesh = cube;

            const NkVec3f centrePied{x, yPied, z};

            pied.transform =
                NkMat4f::Translate(centrePied) *
                NkMat4f::Scale(taillePied);

            pied.tint = {0.35f, 0.18f, 0.08f};

            pied.aabb.min = {
                x - sectionPied / 2.0f,
                yPied - hauteurPied / 2.0f,
                z - sectionPied / 2.0f
            };

            pied.aabb.max = {
                x + sectionPied / 2.0f,
                yPied + hauteurPied / 2.0f,
                z + sectionPied / 2.0f
            };

            r3d->Submit(pied);
        };

        // 12. Les quatre pieds
        dessinerPied(xGauche, zAvant);
        dessinerPied(xGauche, zArriere);
        dessinerPied(xDroite, zAvant);
        dessinerPied(xDroite, zArriere);

        // 13. Presentation
        // Ajouter ici l'etape d'execution de la scene si elle est
        // requise par l'API de rendu utilisee dans ton projet.
        renderer->Present();
        renderer->EndFrame();
    }

    // 14. Nettoyage
    device->WaitIdle();

    NkRenderer::Destroy(renderer);
    NkDeviceFactory::Destroy(device);

    window.Close();

    return 0;
}
