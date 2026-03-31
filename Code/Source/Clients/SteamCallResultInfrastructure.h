/*
 * Copyright (c) 2026 Heathen Engineering Limited
 * Irish Registered Company #556277
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

// Private header — must NOT be included from any public Include/ header.
// Defines the CallResult bridge types and the CallResultRegistry pimpl struct.

#include "FoundationSteamworksSystemComponent.h"
#include "SteamTypeConverters.h"

#include <AzCore/std/containers/unordered_map.h>
#include <AzCore/std/smart_ptr/unique_ptr.h>
#include <AzCore/std/functional.h>

namespace FoundationSteamworks
{
    // -----------------------------------------------------------------------
    // CallResult bridge
    //
    // Each in-flight CallResult lives in a typed CallResultEntry<T> that:
    //   - Stores its own SteamAPICall_t handle, so the handler always has it
    //   - Owns the CCallResult<> (requires stable address — use unique_ptr)
    //   - Holds a dispatch lambda that performs the bus broadcast
    //   - Signals the registry to sweep it after firing
    //
    // The registry is a single unordered_map<handle, unique_ptr<ICallResultEntry>>
    // covering all types. After SteamAPI_RunCallbacks() each tick, completed
    // entries are erased.
    // -----------------------------------------------------------------------

    struct ICallResultEntry
    {
        SteamAPICall_t handle = k_uAPICallInvalid;
        bool fired = false;
        virtual ~ICallResultEntry() = default;
    };

    template<typename T>
    struct CallResultEntry final : ICallResultEntry
    {
        using DispatchFn = AZStd::function<void(Heathen::SteamCallHandle, T*, bool)>;

        CCallResult<CallResultEntry<T>, T> callResult;
        DispatchFn dispatch;

        void Set(SteamAPICall_t h, DispatchFn fn)
        {
            handle = h;
            dispatch = AZStd::move(fn);
            callResult.Set(h, this, &CallResultEntry::OnResult);
        }

        void OnResult(T* p, bool ioFail)
        {
            dispatch(ToCallHandle(handle), p, ioFail);
            fired = true;
        }
    };

    // -----------------------------------------------------------------------
    // CallResultRegistry — owned by the system component via unique_ptr.
    // Keeps Steam types out of the public header.
    // -----------------------------------------------------------------------
    struct FoundationSteamworksSystemComponent::CallResultRegistry
    {
        AZStd::unordered_map<SteamAPICall_t, AZStd::unique_ptr<ICallResultEntry>> pending;

        template<typename T>
        void Register(SteamAPICall_t handle,
                      AZStd::function<void(Heathen::SteamCallHandle, T*, bool)> dispatch)
        {
            if (handle == k_uAPICallInvalid)
                return;
            auto entry = AZStd::make_unique<CallResultEntry<T>>();
            entry->Set(handle, AZStd::move(dispatch));
            pending[handle] = AZStd::move(entry);
        }

        // Call after SteamAPI_RunCallbacks() to release completed entries.
        void Sweep()
        {
            for (auto it = pending.begin(); it != pending.end(); )
            {
                if (it->second->fired)
                    it = pending.erase(it);
                else
                    ++it;
            }
        }

        void Clear()
        {
            pending.clear();
        }
    };

} // namespace FoundationSteamworks
