
#include <AzCore/Serialization/SerializeContext.h>

#include <AzToolsFramework/API/ViewPaneOptions.h>

#include "FoundationSteamworksWidget.h"
#include "FoundationSteamworksEditorSystemComponent.h"

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
    }

    void FoundationSteamworksEditorSystemComponent::GetDependentServices([[maybe_unused]] AZ::ComponentDescriptor::DependencyArrayType& dependent)
    {
        BaseSystemComponent::GetDependentServices(dependent);
    }

    void FoundationSteamworksEditorSystemComponent::Activate()
    {
        FoundationSteamworksSystemComponent::Activate();
        AzToolsFramework::EditorEvents::Bus::Handler::BusConnect();
    }

    void FoundationSteamworksEditorSystemComponent::Deactivate()
    {
        AzToolsFramework::EditorEvents::Bus::Handler::BusDisconnect();
        FoundationSteamworksSystemComponent::Deactivate();
    }

    void FoundationSteamworksEditorSystemComponent::NotifyRegisterViews()
    {
        AzToolsFramework::ViewPaneOptions options;
        options.paneRect = QRect(100, 100, 500, 400);
        options.showOnToolsToolbar = true;
        options.toolbarIcon = ":/FoundationSteamworks/toolbar_icon.svg";

        // Register our custom widget as a dockable tool with the Editor under an Examples sub-menu
        AzToolsFramework::RegisterViewPane<FoundationSteamworksWidget>("FoundationSteamworks", "Examples", options);
    }

} // namespace FoundationSteamworks
