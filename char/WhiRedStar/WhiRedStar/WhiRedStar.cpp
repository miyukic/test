#include "stdafx.h"
#include "WhiRedStar.h"

void WhiRedStar::start() noexcept
{
	// 背景の色を設定 | Set background color
	Scene::SetBackground(ColorF{ 0.0, 0.0, 0.0 });
	// 通常のフォントを作成 | Create a new font
	const Font font{ 60 };
	 // 絵文字用フォントを作成 | Create a new emoji font
	const Font emojiFont{ 60, Typeface::ColorEmoji };
	 // `font` が絵文字用フォントも使えるようにする | Set emojiFont as a fallback
	font.addFallback(emojiFont); 
	// 画像ファイルからテクスチャを作成 | Create a texture from an image file
	const Texture texture{ U"example/windmill.png" }; 
	// 絵文字からテクスチャを作成 | Create a texture from an emoji
	const Texture emoji{ U"🐈"_emoji }; 
	// 絵文字を描画する座標 | Coordinates of the emoji
	Vec2 emojiPos{ 300, 150 }; 
	// テキストを画面にデバッグ出力 | Print a text
	Print << U"Push [A] key";
}

void WhiRedStar::loop() noexcept
{
}
