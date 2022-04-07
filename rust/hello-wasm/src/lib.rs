//──────────────────────────────────────────────────────────────────────────────────
// wasm_bindgenというライブラリを使っている
// Rustではライブラリはクレートという
// 外部(external)のクレートを使っているのでextern
//──────────────────────────────────────────────────────────────────────────────────
extern crate wasm_bindgen;


//──────────────────────────────────────────────────────────────────────────────────
// ライブラリからコードをインポートするuseコマンド
// この場合wasm_bindgen::preludeモジュールにあるものをすべてインポートしている
// wasm_bindgen は RustとJavaScriptの型をつなぐライブラリ
//──────────────────────────────────────────────────────────────────────────────────
use wasm_bindgen::prelude::*;

//──────────────────────────────────────────────────────────────────────────────────
// JavaScript によって提供される alert 関数の定義
// []はアトリビュートという。 後にくる文を修飾している
// extern{}は外部で定義された関数を呼び出したいときに使う文
// アトリビュートはこれらexternの中に書かれた関数を見つける方法を知っているという意味
// alert(s: &str) はJavaScriptのalert()のこと
// JavaScriptの関数を呼び出したいときはここに追加する
//──────────────────────────────────────────────────────────────────────────────────
#[wasm_bindgen]
extern {
    pub fn alert(s: &str);
}

//──────────────────────────────────────────────────────────────────────────────────
// JavaScript が呼び出せる Rust 関数
// ここでのアトリビュート[]はJavaScript側でgreet()関数を呼び出せるようにしてほしい
// という意味
//──────────────────────────────────────────────────────────────────────────────────
#[wasm_bindgen]
pub fn greet(name: &str) {
    alert(&format!("Hello, {}!", name));
}
