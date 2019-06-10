#ifndef APP_H_
#define APP_H_

typedef int(*CMainFunc)(int argc, char* argv[]);
template<typename T, typename MainT>
T main(T argc, char* argv[])
{
	return MainT::main(argc, argv);
}

class App
{
private:
	friend class Startup;
	inline static int main(int argc, char*argv[]) { return 0; }
};

class Startup
{
public:
	inline Startup(CMainFunc main_func){}

	inline static int main(int argc, char* argv[])
	{
		return App::main(argc, argv);
	}
};

const Startup start(&main<int, Startup>);

#endif 


