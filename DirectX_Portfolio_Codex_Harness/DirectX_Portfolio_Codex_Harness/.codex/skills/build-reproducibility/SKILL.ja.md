# ビルド再現性（日本語ミラー）

`.sln/.vcxproj`、実ファイル配置、include/lib、working directory、shader、DLLを確認し、まずVS2022 v143 x64 Debugだけを正本として再現可能にします。このskillではC++設計変更、rename、文字コード変換、D3DX移行、ゲーム仕様変更を行いません。
