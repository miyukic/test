// 以下の ifdef ブロックは、DLL からのエクスポートを容易にするマクロを作成するための
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された LIBRARYTEST_EXPORTS
// シンボルを使用してコンパイルされます。このシンボルは、この DLL を使用するプロジェクトでは定義できません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、
// LIBRARYTEST_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。
#ifdef LIBRARYTEST_EXPORTS
#define LIBRARYTEST_API __declspec(dllexport)
#else
#define LIBRARYTEST_API __declspec(dllimport)
#endif
#include <vector>

// このクラスは dll からエクスポートされました
class LIBRARYTEST_API CLibraryTest {
	std::vector<int> vec = std::vector<int>(10);
public:
	CLibraryTest(void);
	int GetNumber(void);
	// TODO: メソッドをここに追加します。
};

extern LIBRARYTEST_API int nLibraryTest;

LIBRARYTEST_API int fnLibraryTest(int value);
