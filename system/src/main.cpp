#include "ce2/modules/pe/player_debug.hpp"
#include "loader_base.hpp"

namespace CEPE = CE_NS ModulePE;

int main() {
	CE_PL_NS _ScriptLoaderImpl::Init();
	CEPE::PlayerDebug::Init();
    
	CEPE::PlayerDebug::Main();
}