#include <string>
#include <functional>
#include <map>

class Router{
private:
  std::map<std::string,std::function<void(std::string)>> m_routes;
public:
  Router() = default;
  Router(const Router&) = delete;
  Router(const Router&&) = delete;
  Router& operator = (const Router&) = delete;
  Router& operator = (const Router&&) = delete;
  
  template <typename Url,typename Callback>
	void add(Url&& url,Callback&& callback)
	{
    	m_routes[url] = callback;
	}
 void dispatch(const char* url)
  {
    for(std::map<std::string,std::function<void(std::string)>>::iterator it= m_routes.begin(); it!=m_routes.end();it++)
    {
     	if(it->first == url){
        	std::invoke(it->second,it->first);
        }
    }
  }
  
}router;

struct HomeController{
void getUserHome(){}
}homeController;

int main([[maybe_unused]] int argc,[[maybe_unused]]const char* argv[])
{
	router.add("/home",[]([[maybe_unused]]std::string url){
      return std::invoke(&HomeController::getUserHome,homeController);
    });
   router.dispatch(argv[1]);
}
