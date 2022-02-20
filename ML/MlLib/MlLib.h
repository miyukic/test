// 以下の ifdef ブロックは、DLL からのエクスポートを容易にするマクロを作成するための
// 一般的な方法です。この DLL 内のすべてのファイルは、コマンド ラインで定義された MLLIB_EXPORTS
// シンボルを使用してコンパイルされます。このシンボルは、この DLL を使用するプロジェクトでは定義できません。
// ソースファイルがこのファイルを含んでいる他のプロジェクトは、
// MLLIB_API 関数を DLL からインポートされたと見なすのに対し、この DLL は、このマクロで定義された
// シンボルをエクスポートされたと見なします。
#ifdef MLLIB_EXPORTS
#define MLLIB_API __declspec(dllexport)
#else
#define MLLIB_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
	// このクラスは dll からエクスポートされました
	//class MLLIB_API CMlLib {
	//public:
	//	CMlLib(void);
	//	// TODO: メソッドをここに追加します。
	//};

	//extern MLLIB_API int nMlLib;


	MLLIB_API int fnMlLib(void);

#ifdef __cplusplus
}
#endif
