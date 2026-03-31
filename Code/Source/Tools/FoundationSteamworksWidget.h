
#pragma once

#if !defined(Q_MOC_RUN)
#include <AzToolsFramework/API/ToolsApplicationAPI.h>

#include <QWidget>
#endif

namespace FoundationSteamworks
{
    class FoundationSteamworksWidget
        : public QWidget
    {
        Q_OBJECT
    public:
        explicit FoundationSteamworksWidget(QWidget* parent = nullptr);
    };
} 
