
#include <AzCore/Serialization/SerializeContext.h>
#include <AzCore/Interface/Interface.h>

#include "FoundationSteamworksEditorSystemComponent.h"
#include "SteamworksSettingsPage.h"

#include <EditorExtensions/ISettingsPageRegistry.h>
#include <FoundationSteamworks/FoundationSteamworksTypeIds.h>

namespace FoundationSteamworks
{
    AZ_COMPONENT_IMPL(FoundationSteamworksEditorSystemComponent, "FoundationSteamworksEditorSystemComponent",
        FoundationSteamworksEditorSystemComponentTypeId, BaseSystemComponent);

    void FoundationSteamworksEditorSystemComponent::Reflect(AZ::ReflectContext* context)
    {
        if (auto serializeContext = azrtti_cast<AZ::SerializeContext*>(context))
        {
            serializeContext->Class<FoundationSteamworksEditorSystemComponent, FoundationSteamworksSystemComponent>()
                ->Version(0);
        }
    }

    FoundationSteamworksEditorSystemComponent::FoundationSteamworksEditorSystemComponent() = default;

    FoundationSteamworksEditorSystemComponent::~FoundationSteamworksEditorSystemComponent() = default;

    void FoundationSteamworksEditorSystemComponent::GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided)
    {
        BaseSystemComponent::GetProvidedServices(provided);
        provided.push_back(AZ_CRC_CE("FoundationSteamworksEditorService"));
    }

    void FoundationSteamworksEditorSystemComponent::GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible)
    {
        BaseSystemComponent::GetIncompatibleServices(incompatible);
        incompatible.push_back(AZ_CRC_CE("FoundationSteamworksEditorService"));
    }

    void FoundationSteamworksEditorSystemComponent::GetRequiredServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& required)
    {
        BaseSystemComponent::GetRequiredServices(required);
        required.push_back(AZ_CRC_CE("EditorExtensionsService"));
    }

    void FoundationSteamworksEditorSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        BaseSystemComponent::GetDependentServices(dependent);
    }

    void FoundationSteamworksEditorSystemComponent::Activate()
    {
        FoundationSteamworksSystemComponent::Activate();
        AzToolsFramework::EditorEvents::Bus::Handler::BusConnect();

        if (auto* reg = AZ::Interface<EditorExtensions::ISettingsPageRegistry>::Get())
            reg->RegisterPage(AZStd::make_unique<SteamworksSettingsPage>());
    }

    void FoundationSteamworksEditorSystemComponent::Deactivate()
    {
        AzToolsFramework::EditorEvents::Bus::Handler::BusDisconnect();
        FoundationSteamworksSystemComponent::Deactivate();
    }

    void FoundationSteamworksEditorSystemComponent::NotifyRegisterViews()
    {
        // FoundationSteamworks has no dedicated editor tool window.
    }

} // namespace FoundationSteamworks
