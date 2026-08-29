# Rename Map

Record rename-only work here before applying it.

| Status | Old name | Proposed name | Scope | Reason | Behavior impact |
|---|---|---|---|---|---|
| proposed | `collitionBox.*` / `CollisionBox` references | `collisionBox.*` / `CollisionBox` | file/include names | spelling/readability | none intended |
| proposed | `baceCampObj.*` / `BaceCampObj` | `baseCampObj.*` / `BaseCampObj` | file/type | spelling | none intended |
| proposed | `sprit2D.*` / `Sprit2D` | `sprite2D.*` / `Sprite2D` | file/type | spelling | none intended |
| proposed | `recepitionPointer.*` | `receptionPointer.*` | file/type | spelling | none intended |
| proposed | `GetFlam` / `SetFlam` / `g_Flame` | `GetFrameRate` / `SetFrameRate` / `g_FrameRate` | app timing | clarify likely intent | none intended; verify semantics |

Do not apply all rows at once. Confirm public API/include impact and update this table with the actual commit.
