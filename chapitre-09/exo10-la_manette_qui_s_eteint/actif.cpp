// actif.cpp — Exercice 10 : « La manette qui s'éteint »
// Corrige le comportement de préhension lorsqu'une manette passe en veille / s'éteint.

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
    d.appName = "ManetteEteinte";
}
NK_REGISTER_ENTRY_APPDATA_UPDATER(ConfigureAppData)

int nkmain(const NkEntryState &state) {
    (void)state;

    // Déclaration du jeu d'actions
    nkxr::NkXrActionSet actionSet;

    const nkxr::NkXrActionHandle actGrab = actionSet.CreateAction({
        "saisir",
        nkxr::NkXrActionType::NK_XR_ACTION_BOOL,
        nkxr::NkXrActionUsage::NK_XR_USAGE_GRAB
    });

    const nkxr::NkXrActionHandle actPalmPose = actionSet.CreateAction({
        "paume_droite",
        nkxr::NkXrActionType::NK_XR_ACTION_POSE,
        nkxr::NkXrActionUsage::NK_XR_USAGE_GRIP_POSE
    });

    bool objetTenu = false;
    NkVec3f objetPosition{0.f, 0.f, 0.f};
    NkQuatf objetOrientation{};

    // Gestion de la frame et de la mise en veille
    auto TraiterPrehension = [&](const nkxr::NkXrActionStateBool &grabState,
                                 const nkxr::NkXrPose &palmPose) {

        /*
        // =====================================================================
        // CODE NAÏF (AVANT CORRECTION) :
        // =====================================================================
        // Ne teste que grabState.current sans vérifier grabState.active.
        // Quand la manette s'éteint, le runtime OpenXR force grabState.current à 0.
        // Le code l'interprète faussement comme un relâchement volontaire et
        // laisse tomber l'objet (cf. avant.png).
        if (grabState.current) {
            objetTenu = true;
            objetPosition = palmPose.position;
            objetOrientation = palmPose.orientation;
        } else {
            // L'objet tombe dès que la manette s'éteint !
            objetTenu = false;
        }
        */

        // =====================================================================
        // CODE CORRIGÉ (TEST DU CHAMP ACTIF) :
        // =====================================================================
        // On ne lâche l'objet QUE si :
        // 1) L'action est active (grabState.active == true, la manette est connectée et allumée)
        // 2) ET le relâchement est un front réel (grabState.changed == true && !grabState.current)
        if (grabState.active && grabState.current) {
            // Manette allumée et gâchette maintenue : l'objet suit la paume
            objetTenu = true;
            objetPosition = palmPose.position;
            objetOrientation = palmPose.orientation;
        } else if (grabState.active && grabState.changed && !grabState.current) {
            // Relâchement volontaire valide : la manette est active et le joueur ouvre la main
            objetTenu = false;
        } else if (!grabState.active) {
            // La manette s'est éteinte (grabState.active == false) :
            // Ce n'est PAS un relâchement volontaire du joueur.
            // On conserve l'objet tenu à sa dernière pose connue pour éviter toute perte accidentelle.
            // objetTenu reste à true !
        }
    };

    (void)TraiterPrehension;
    (void)actGrab;
    (void)actPalmPose;
    (void)objetTenu;

    return 0;
}
