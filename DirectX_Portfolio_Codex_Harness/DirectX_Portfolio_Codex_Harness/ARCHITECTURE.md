# Architecture — Observed Legacy Design

## Runtime flow

```text
WinMain
  -> Manager::Init
      -> Renderer::Init
      -> Input::Init
      -> Audio::InitMaster
      -> ImGui init
      -> Manager::SetScene<Title>()
  -> frame loop (~60 FPS target)
      -> Manager::Update
          -> Input::Update
          -> scene transition
          -> Scene::Update
              -> GameObject::Update
                  -> Component::Update
      -> Manager::Draw
          -> Renderer::Begin
          -> Scene::Draw
          -> ImGui render
          -> Renderer::End
```

## Main subsystems observed

| Subsystem | Representative files | Observed responsibility |
|---|---|---|
| Application/loop | `main.cpp`, `manager.*` | Win32 window, frame pacing, scene lifetime, ImGui frame lifecycle |
| Scene graph | `scene.h`, `gameObject.h`, `component.h` | 3-layer object lists, object/component update/draw, deletion flags |
| Rendering | `renderer.*`, `drawModel.*`, `model.*`, `animationModel.*` | Direct3D 11 device/state, OBJ/Assimp model rendering, dynamic animated vertices |
| Shaders | runtime `shader/*.hlsl` | pixel lighting, rim lighting, shadow mapping, dissolve, unlit textured rendering |
| Animation | `animationModel.*` | Assimp skeletal animation loading, animation blending, CPU skinning |
| Collision | `collitionBox.*`, `villageObjCollition.*` | OBB collision using separating-axis tests |
| Player/combat | `player.*`, `weapon.*`, special attacks, bullets/effects | stateful movement/combat, weapon/effect logic |
| Enemy AI | `enemy.*`, jump/remote attack files | search/found/chase/attack/death state behavior and field-of-view check |
| Game scenes | `title.*`, `game.*`, `village.*`, `tutorial.*`, `result.*`, `loading.*` | scene-specific setup, transitions, gameplay |
| UI/economy | `ui01.*`, `villageUi.*`, `questDeskUi.*`, store UIs, `money.*`, scores | HUD, quest/shop flows, currency/material display |
| Audio/input | `audio.*`, `input.*` | XAudio2 WAV playback and keyboard state polling |
| Assets/deps | runtime `asset/`, `assimp/`, `imgui/` | content and third-party code |

## Notable technical features worth preserving in the portfolio narrative

- Direct3D 11 renderer and Win32 application loop.
- HLSL shadow mapping, rim lighting, dissolve effect, and textured rendering.
- Skeletal animation import/blending with Assimp and CPU skinning.
- OBB collision based on separating axes.
- Multiple gameplay scenes and an object/component abstraction.
- Enemy state behavior including detection/chase/attack variants.
- Combat, weapons, special attacks, quest/store UI, currency/items.
- XAudio2 audio and Dear ImGui integration.

## Architectural pressure points

- Global/static service access (`Manager`, `Renderer`, `Input`, audio master).
- Raw owning pointers across scene objects, components, UI sprites, model data, and COM objects.
- Lifetime is encoded through `Init/Uninit` conventions rather than C++ destructors/RAII.
- `GameObject::Destroy()` self-deletes, while `Scene` also owns object pointers.
- Large update functions mix input, state transitions, animation timing, collision, and side effects.
- Rendering/resource creation is tightly coupled to gameplay object classes.
- Hard-coded asset paths and gameplay coordinates make data ownership unclear.

This document describes the current code; it is not a demand to replace every pattern. Modernization must follow the phased plan.
