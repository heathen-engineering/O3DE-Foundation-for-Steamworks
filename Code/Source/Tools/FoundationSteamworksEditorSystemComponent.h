
#pragma once

#include <Clients/FoundationSteamworksSystemComponent.h>

#include <AzToolsFramework/Entity/EditorEntityContextBus.h>

namespace FoundationSteamworks
{
    /// System component for FoundationSteamworks editor
    class FoundationSteamworksEditorSystemComponent
        : public FoundationSteamworksSystemComponent
        , protected AzToolsFramework::EditorEvents::Bus::Handler
    {
        using BaseSystemComponent = FoundationSteamworksSystemComponent;
    public:
        AZ_COMPONENT_DECL(FoundationSteamworksEditorSystemComponent);

        static void Reflect(AZ::ReflectContext* context);

        FoundationSteamworksEditorSystemComponent();
        ~FoundationSteamworksEditorSystemComponent();

    private:
        static void GetProvidedServices(AZ::ComponentDescriptor::DependencyArrayType& provided);
        static void GetIncompatibleServices(AZ::ComponentDescriptor::DependencyArrayType& incompatible);
        static void GetRequiredServices(AZ::ComponentDescriptor::DependencyArrayType& required);
        static void GetDependentServices(AZ::ComponentDescriptor::DependencyArrayType& dependent);

        // AZ::Component
        void Activate() override;
        void Deactivate() override;

        // AzToolsFramework::EditorEventsBus overrides ...
        void NotifyRegisterViews() override;
    };
} // namespace FoundationSteamworks
