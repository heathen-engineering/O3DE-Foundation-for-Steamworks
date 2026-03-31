
#include <FoundationSteamworks/FoundationSteamworksTypeIds.h>
#include <FoundationSteamworksModuleInterface.h>
#include "FoundationSteamworksSystemComponent.h"

namespace FoundationSteamworks
{
    class FoundationSteamworksModule
        : public FoundationSteamworksModuleInterface
    {
    public:
        AZ_RTTI(FoundationSteamworksModule, FoundationSteamworksModuleTypeId, FoundationSteamworksModuleInterface);
        AZ_CLASS_ALLOCATOR(FoundationSteamworksModule, AZ::SystemAllocator);
    };
}// namespace FoundationSteamworks

#if defined(O3DE_GEM_NAME)
AZ_DECLARE_MODULE_CLASS(AZ_JOIN(Gem_, O3DE_GEM_NAME), FoundationSteamworks::FoundationSteamworksModule)
#else
AZ_DECLARE_MODULE_CLASS(Gem_FoundationSteamworks, FoundationSteamworks::FoundationSteamworksModule)
#endif
