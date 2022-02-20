// MlLib.cpp : DLL 用にエクスポートされる関数を定義します。
//

#include "pch.h"
#include "framework.h"
#include "MlLib.h"


// これは、エクスポートされた変数の例です
//MLLIB_API int nMlLib=0;

// これは、エクスポートされた関数の例です。
MLLIB_API int fnMlLib(void)
{
    return 256 * 3;
}


// これは、エクスポートされたクラスのコンストラクターです。
//CMlLib::CMlLib()
//{
//    return;
//}
