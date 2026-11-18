// saisie.cpp — Exercice 9 : « Tenir un objet, et le laisser tomber »
// Démontre la différence entre une saisie attachée sur le front et un maintien sur le niveau.

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

#include "NKXR/NKXR.h"

using namespace nkentseu;
using namespace nkentseu::renderer;
namespace nkxr = nkentseu::xr;

static void ConfigureAppData(NkAppData &d) {
    d.appName = "SaisieObjet";
}
NK_REGISTER_ENTRY_APPDATA_UPDATER(ConfigureAppData)

int nkmain(const NkEntryState &state) {
    (void)state;

    // ── 1. Initialisation de la session XR et déclaration des actions ────────
    // Le jeu d'actions déclare l'intention de saisir et la pose de la main droite.
    nkxr::NkXrActionSet actionSet;

    // Action booléenne pour la commande de saisie (grip droit)
    const nkxr::NkXrActionHandle actGrab = actionSet.CreateAction({
        "saisir",
        nkxr::NkXrActionType::NK_XR_ACTION_BOOL,
        nkxr::NkXrActionUsage::NK_XR_USAGE_GRAB
    });

    // Pose de la main : ATTENTION AU PIÈGE — on utilise la pose de la PAUME (GRIP_POSE)
    // et JAMAIS la pose de visée (AIM_POSE) pour attacher un objet tenu.
    const nkxr::NkXrActionHandle actPalmPose = actionSet.CreateAction({
        "paume_droite",
        nkxr::NkXrActionType::NK_XR_ACTION_POSE,
        nkxr::NkXrActionUsage::NK_XR_USAGE_GRIP_POSE
    });

    // ── 2. État de la préhension ─────────────────────────────────────────────
    bool objetTenu = false;
    NkVec3f objetPosition{0.f, 0.f, 0.f};
    NkQuatf objetOrientation{};
    const NkVec3f tailleCube{0.2f, 0.2f, 0.2f};

    // ── 3. Boucle de simulation / frame ──────────────────────────────────────
    // À chaque trame, les actions sont synchronisées puis interrogées.
    auto MettreAJourPrehension = [&](const nkxr::NkXrActionStateBool &grabState,
                                     const nkxr::NkXrPose &palmPose) {

        /*
        // =====================================================================
        // VERSION 1 (FAUSSE) : attachement sur le front uniquement
        // =====================================================================
        // Si l'on teste le front montant (current && changed), l'objet n'est attaché
        // qu'à la première frame d'appui. Dès la frame suivante, grabState.changed
        // repasse à faux même si le joueur maintient la gâchette enfoncée. L'objet
        // n'étant plus attaché, il glisse de la main et tombe au sol (cf. front.png).
        if (grabState.current && grabState.changed) {
            objetTenu = true;
            objetPosition = palmPose.position;
            objetOrientation = palmPose.orientation;
        } else {
            // Perdu dès la trame suivante car changed == false !
            objetTenu = false;
        }
        */

        // =====================================================================
        // VERSION 2 (CORRECTE) : maintien continu sur le niveau
        // =====================================================================
        // Un objet se tient sur un NIVEAU (grabState.current).
        // Tant que grabState.current est vrai, l'objet reste solidaire de la paume (GRIP_POSE).
        if (grabState.current) {
            objetTenu = true;
            objetPosition = palmPose.position;
            objetOrientation = palmPose.orientation;
        } else if (grabState.changed && !grabState.current) {
            // Relâchement volontaire détecté sur le front descendant (changed == true et current == false)
            objetTenu = false;
        }
    };

    (void)MettreAJourPrehension;
    (void)actGrab;
    (void)actPalmPose;
    (void)objetTenu;
    (void)tailleCube;

    return 0;
}
