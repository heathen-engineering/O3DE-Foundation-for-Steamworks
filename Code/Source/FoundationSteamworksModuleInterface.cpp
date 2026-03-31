
#include "FoundationSteamworksModuleInterface.h"
#include <AzCore/Memory/Memory.h>

#include <FoundationSteamworks/FoundationSteamworksTypeIds.h>

#include <Clients/FoundationSteamworksSystemComponent.h>

namespace FoundationSteamworks
{
    AZ_TYPE_INFO_WITH_NAME_IMPL(FoundationSteamworksModuleInterface,
        "FoundationSteamworksModuleInterface", FoundationSteamworksModuleInterfaceTypeId);
    AZ_RTTI_NO_TYPE_INFO_IMPL(FoundationSteamworksModuleInterface, AZ::Module);
    AZ_CLASS_ALLOCATOR_IMPL(FoundationSteamworksModuleInterface, AZ::SystemAllocator);

    FoundationSteamworksModuleInterface::FoundationSteamworksModuleInterface()
    {
        // Push results of [MyComponent]::CreateDescriptor() into m_descriptors here.
        // Add ALL components descriptors associated with this gem to m_descriptors.
        // This will associate the AzTypeInfo information for the components with the the SerializeContext, BehaviorContext and EditContext.
        // This happens through the [MyComponent]::Reflect() function.
        m_descriptors.insert(m_descriptors.end(), {
            FoundationSteamworksSystemComponent::CreateDescriptor(),
            });
    }

    AZ::ComponentTypeList FoundationSteamworksModuleInterface::GetRequiredSystemComponents() const
    {
        return AZ::ComponentTypeList{
            azrtti_typeid<FoundationSteamworksSystemComponent>(),
        };
    }
} // namespace FoundationSteamworks
