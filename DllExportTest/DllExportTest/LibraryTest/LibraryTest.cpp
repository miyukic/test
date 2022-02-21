// LibraryTest.cpp : DLL 用にエクスポートされる関数を定義します。
//

#include "pch.h"
#include "framework.h"
#include "LibraryTest.h"


// これは、エクスポートされた変数の例です
LIBRARYTEST_API int nLibraryTest=0;

// これは、エクスポートされた関数の例です。
LIBRARYTEST_API int fnLibraryTest(void)
{
    return 32;
}

// これは、エクスポートされたクラスのコンストラクターです。
CLibraryTest::CLibraryTest()
{
    return;
}
