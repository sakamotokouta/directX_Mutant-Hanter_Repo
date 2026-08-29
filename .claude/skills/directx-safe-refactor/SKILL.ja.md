# DirectX Safe Refactor — 日本語説明

挙動維持を最優先するC++リファクタリング用です。編集前に所有者/参照者、state遷移、Update/Draw順、asset/shader path、animation frame、collision thresholdなどの不変条件を整理し、1タスク1テーマで変更します。`archive/original/**`を変更せず、新しいraw owning pointerや`delete this`を増やさず、実際に行った検証だけを記録します。
