# C++ Safety Rules — 日本語ミラー

- pointer変更前に所有/非所有を判定。
- 単独所有のみ`unique_ptr`、observerを安易に`shared_ptr`へしない。
- 新しいraw owning `new/delete`と`delete this`を作らない。
- polymorphic delete前にvirtual destructorを確認。
- 構造変更中はUpdate/Draw順、scene遷移、collision threshold、animation frame、ゲーム定数を変えない。
- 大関数分割でもbranch/state遷移順を維持。
- 未変更コードまで一括整形せずdiffを読みやすくする。
