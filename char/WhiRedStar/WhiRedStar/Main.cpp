﻿#include <Siv3D.hpp> // OpenSiv3D v0.6.4
#include "WhiRedStar.h"

void Main()
{
	
	WhiRedStar::start();
	while (System::Update())
	{
		WhiRedStar::loop();
	}
}

//
// - Debug ビルド: プログラムの最適化を減らす代わりに、エラーやクラッシュ時に詳細な情報を得られます。
//
// - Release ビルド: 最大限の最適化でビルドします。
//
// - [デバッグ] メニュー → [デバッグの開始] でプログラムを実行すると、[出力] ウィンドウに詳細なログが表示され、エラーの原因を探せます。
//
// - Visual Studio を更新した直後は、プログラムのリビルド（[ビルド]メニュー → [ソリューションのリビルド]）が必要です。
//
// Siv3D リファレンス
// https://zenn.dev/reputeless/books/siv3d-documentation
//
// Siv3D Reference
// https://zenn.dev/reputeless/books/siv3d-documentation-en
//
// Siv3D コミュニティへの参加（Slack や Twitter, BBS で気軽に質問や情報交換ができます）
// https://zenn.dev/reputeless/books/siv3d-documentation/viewer/community
//
// Siv3D User Community
// https://zenn.dev/reputeless/books/siv3d-documentation-en/viewer/community
//
// 新機能の提案やバグの報告 | Feedback
// https://github.com/Siv3D/OpenSiv3D/issues
//
// Sponsoring Siv3D
// https://github.com/sponsors/Reputeless
//
//		// テクスチャを描く | Draw a texture
//		texture.draw(200, 200);
//
//		// テキストを画面の中心に描く | Put a text in the middle of the screen
//		font(U"Hello, Siv3D!🚀").drawAt(Scene::Center(), Palette::Black);
//
//		// サイズをアニメーションさせて絵文字を描く | Draw a texture with animated size
//		emoji.resized(100 + Periodic::Sine0_1(1s) * 20).drawAt(emojiPos);
//
//		// マウスカーソルに追随する半透明な円を描く | Draw a red transparent circle that follows the mouse cursor
//		Circle{ Cursor::Pos(), 40 }.draw(ColorF{ 1, 0, 0, 0.5 });
//
//		// もし [A] キーが押されたら | When [A] key is down
//		if (KeyA.down())
//		{
//			// 選択肢からランダムに選ばれたメッセージをデバッグ表示 | Print a randomly selected text
//			Print << Sample({ U"Hello!", U"こんにちは", U"你好", U"안녕하세요?" });
//		}
//
//		// もし [Button] が押されたら | When [Button] is pushed
//		if (SimpleGUI::Button(U"Button", Vec2{ 640, 40 }))
//		{
//			// 画面内のランダムな場所に座標を移動
//			// Move the coordinates to a random position in the screen
//			emojiPos = RandomVec2(Scene::Rect());
//		}
