# Foundation for Steamworks (O3DE Gem)

A thin, O3DE-centric wrapper over the Steamworks SDK that exposes Steam functionality to O3DE scripting and engine systems.

This gem provides direct access to Steamworks interfaces through O3DE-native patterns, replacing Valve types with engine-aligned equivalents and exposing callbacks through O3DE event buses.

---

## Core Concept

The Foundation for Steamworks is not a gameplay framework. It is a binding layer.

It:
- Wraps the Steamworks SDK
- Translates Steam types into O3DE-native equivalents
- Exposes Steam interfaces via O3DE Event Buses
- Normalises callback flow into engine-style events

---

## Design Approach

This system is intentionally O3DE-centric rather than a direct SDK mirror.

Key design rules:
- No direct exposure of raw Steamworks types to gameplay code
- All Steam callbacks are routed through O3DE Event Buses
- Steam interfaces map to corresponding O3DE bus abstractions
- Native Steam structures are mirrored with engine-safe equivalents

---

## Event Model

Each Steamworks interface has a corresponding O3DE Event Bus.

- Steam callbacks are translated into bus events
- Event delivery follows O3DE messaging patterns
- Systems subscribe using standard engine bus mechanisms

This replaces direct callback binding with engine-native event flow.

---

## Type System

All Valve Steamworks types are mapped into O3DE equivalents.

- Steam structs → O3DE data structures
- Steam enums → O3DE enum types
- Steam identifiers → engine-safe wrappers where required

This ensures Steam data can be used without dependency leakage into gameplay or tooling layers.

---

## Scope

This gem provides:
- Direct Steamworks SDK integration
- O3DE-style event exposure of Steam callbacks
- Type translation layer between Steam and O3DE systems
- Stable foundation for higher-level tooling

---

## Intended Usage

This gem is designed to be used as a base dependency for higher-level systems, including:

- Toolkit for Steamworks (proprietary layer, built on top)
- Gameplay systems requiring Steam integration
- Engine-level services interacting with Steam APIs
