# 时间与日期

> c++ 一直以来缺乏对时间和日期的处理能力，而时间和日期又是现实生活中经常遇到的，c++程序员不得不求助于c,使用笨拙的结构和函数(struct tm、time())。无法忍受这一情形的程序员则手工构造了自己的实现以满足开发所需，可以想象，有无数的程序员在这方面重复了大量的工作。

> 而现在，Boost使用timer和date_time库完美地解决了这个问题。


---
# 1.1 timer库概述
> timer是一个很小的库，提供简易的度量时间和进度显示功能，可以用于性能测试等需要计时的任务，对于大多数的情况它足够用。

> timer库包含三个组件，分别是：计时器类timer、progress_timer 和进度指示类 progress_display，以下将分别详述。

---
# 1.2 timer
> timer类可以测量时间的流逝，是一个小型的计时器，提供毫秒级别的计时精度和操作函数，供程序员手工控制使用，就像是个方便的秒表。

> timer位于名字空间boost，为了使用timer组件，需要包含头文件〈boost/timer.hpp>，即:
 
```
#include <boost/timer.hpp>  //timer的头文件
using namespace boost;      //打开booost名字空间
```

## 1.2.1 用法
> 让我们通过一段示例代码来看一下如何使用timer。

```
#include <boost/timer.hpp>//timer的头文件
#include <iostream>//标准输入输出流

using namespace boost;//打开booost名字空间
using namespace std;//打开std名字空间

int main(int argc, char *argv[])
{
	timer t;//声明一个计时器对象,开始计时

	cout << "max timespan:" << t.elapsed_max() / 3600 << "h" << endl;//可度量的最大时间,以小时为单位
	cout << "min timespan:" << t.elapsed_min() << "s" << endl;//可度量的最小时间,以秒为单位
	
	//输出已经流逝的时间
	cout << "now time elapsed:" << t.elapsed() << "s" << endl;
	
	system("pause");
	return 0;
}
```

> 上面的代码基本说明了timer的接口。timer对象一旦被声明，它的构造函数就启动了计
> 时工作，之后就可以随时用elapsed()函数简单地测量自对象创建后所流逝的时间。成员函数
> elapsed_min()返回timer测量时间的最小精度，elapsed_max()返回timer能够测量的最
> 大时间范围，两者的单位都是秒。

> 程序的输出如下所示:

```
max timespan:596.523h
min timespan:0.001s
now time elapsed:0.024s
请按任意键继续. . .
```

## 1.2.2 类摘要
> timer类非常小，全部实现包括所有注释也不过70余行，真正的实现代码则只有不到20行。作为我们学习的第一个Boost组件，值得把源码列出来仔细研究：

```
class timer
{
 public:
         timer() { _start_time = std::clock(); } // postcondition: elapsed()==0
//         timer( const timer& src );      // post: elapsed()==src.elapsed()
//        ~timer(){}
//  timer& operator=( const timer& src );  // post: elapsed()==src.elapsed()
  void   restart() { _start_time = std::clock(); } // post: elapsed()==0
  double elapsed() const                  // return elapsed time in seconds
    { return  double(std::clock() - _start_time) / CLOCKS_PER_SEC; }

  double elapsed_max() const   // return estimated maximum value for elapsed()
  // Portability warning: elapsed_max() may return too high a value on systems
  // where std::clock_t overflows or resets at surprising values.
  {
    return (double((std::numeric_limits<std::clock_t>::max)())
       - double(_start_time)) / double(CLOCKS_PER_SEC); 
  }

  double elapsed_min() const            // return minimum value for elapsed()
   { return double(1)/double(CLOCKS_PER_SEC); }

 private:
  std::clock_t _start_time;
}; // timer

```
> timer 的计时使用了标准库头文件<ctime>里的 std::clock()函数，它返回自进程启动以来的clock数，每秒的clock数则由宏 CLOCKS_PER_SEC 定义。CLOCKS_PER_SEC 的值因操作系统而不同，在win32下是1000，而在Linux下则是1000000，也就是说在win32下的精度是毫秒，而Linux下的精度是微秒。

> timer的构造函数记录当前的clock数作为计时起点，保存在私有成员变量_start_time中，每当调用elapsed()时就获取此时的clock数，减去计时起点_start_time，再除以CLOCKS_PER_SEC获得以秒为单位的已经流逝的时间。如果调用函数restart()，则重置_start_time重新开始计时。



> 函数elapsed_min()返回timer能够测量的最小时间单位，是CLOCKS_PER_SEC的倒数。函数elapsed_max()使用了标准库的数值极限类numeric_limits，获得clock_t类型的最大值，采用类似elapsed()的方式计算可能的最大时间范围。
> 


> timer没有定义析构函数，这样做是正确且安全的，因为它仅有一个类型为clock_t的成员变量_start_time，故没有必要实现析构函数来特意“释放资源”(也无资源可供释放)。



## 1.2.3使用建议



> timer接口简单，轻巧好用，适用于大部分的程序计时任务，但使用时我们必须理解elapsed_min()和elapsed_max()这两个计时精度函数的含义，它们表明了timer的能力。timer不适合高精度的时间测量任务，它的精度依赖于操作系统或编译器，难以做到跨平台。timer也不适合大跨度时同段的测量，可提供的最大时间跨度只有几百个小时，如果需要以天、月甚至年作为时同的单位则不能使用timer，应转向date_time库。
> 

# 1.3 progress_timer 

---
> progress_timer 也是一个计时器，它继承自timer，会在析构时自动输出时间，省去了timer手动调用elapsed()的工作，是一个用于自动计时相当方便的小工具。

> progress_timer 位于名字空间boost，为了使用progress_timer组件，需要包含头文件<boost/progress.hpp>，即：

```
#include <boost/progress.hpp>
using namespace boost;
```

## 1.3.1 用法
> progress_timer 继承了timer的全部能力，可以如timer那样使用，例如：

```
progress_timer t;           //声明一个process_timer对象
...                         //任意计算、处理工作
cout<<t.elapsed()<<endl;    //输出流逝的时间
```

> 但它有更简单的使用方法，不需要任何的调用，只要申明progress_timer对象就可以了：

```
#include <boost/progress.hpp>

int main(int argc, char *argv[])
{
	{
		boost::progress_timer t;//声明对象开始计时
		//do something ...
	}//退出作用域，调用progress_timer的析构函数

	system("pause");
	return 0;
}

```
> 这样，在程序退出（准确的说是离开main函数局部域）导致progress_timer析构时，会自动输出流逝的时间。显示输出如下：


```
0.00 s

请按任意键继续. . .
```
> 就这些了，只需要申明progress_timer实例就完成了所需的所有工作，非常容易使用。有了progress_timer，程序员今后在做类似性能测试等计算时间的工作时将会感到轻松很多。

## 1.3.2 类摘要
> progress_timer 的类摘要如下：

```
class progress_timer : public timer, private noncopyable
{
  
 public:
  explicit progress_timer( std::ostream & os = std::cout )
     // os is hint; implementation may ignore, particularly in embedded systems
     : timer(), noncopyable(), m_os(os) {}
  ~progress_timer()
  {
  //  A) Throwing an exception from a destructor is a Bad Thing.
  //  B) The progress_timer destructor does output which may throw.
  //  C) A progress_timer is usually not critical to the application.
  //  Therefore, wrap the I/O in a try block, catch and ignore all exceptions.
    try
    {
      // use istream instead of ios_base to workaround GNU problem (Greg Chicares)
      std::istream::fmtflags old_flags = m_os.setf( std::istream::fixed,
                                                   std::istream::floatfield );
      std::streamsize old_prec = m_os.precision( 2 );
      m_os << elapsed() << " s\n" // "s" is System International d'Unites std
                        << std::endl;
      m_os.flags( old_flags );
      m_os.precision( old_prec );
    }

    catch (...) {} // eat any exceptions
  } // ~progress_timer

 private:
  std::ostream & m_os;
};
```
> progress_timer 继承自timer，因此它的接口与timer相同，也很简单。唯一需要注意的是构造函数progress_timer(std::ostream& os)，它允许将析构时的输出定向到指定的IO流里，默认是std::cout。如果有特别的需求，可以用其他标准输出流(ofstream、ostringstream)替换，或者用cout.rdbuf()重定向cout的输出（但需记得及时的恢复cout的状态以免发生未知错误）。

> 例如，下面的代码吧progress_timer的输出转移到了stringstream中，它可以被转换为字符串供其他应用使用：

```
#include <iostream>
#include <boost/progress.hpp>
#include <sstream>

using namespace std;
using namespace boost;

int main(int argc, char *argv[])
{
	stringstream ss;

	{
		progress_timer pt(ss);
		//do something ...
	}

	cout << ss.str() << endl;
	system("pause");
	
	return 0;
}

```
> 输出如下：
```
0.00 s

请按任意键继续. . .
```
## 1.3.3 拓展计时精度

> progress_timer 用于即使非常方便，但可惜的是它对外输出精度只有小数点后两位，即只精确到百分之一秒。但实际上timer内部计时_start_time是个double值，从timer.elapsed_min()可以知道，在win32平台精度最小能达到毫秒，在linux平台则可以精确到微妙。

> 如果需要更高的时间精度，可以直接修改progress_timer的代码，把输出精度改为需要的值，但这不是一个好主意，原则上程序库的代码是不应该被用户修改的。合理的做法是使用“开-闭”原则脱焊progress_timer库。

> “开-闭”原则的思想是对拓展开放二对修改关闭，但很遗憾，progress_timer也并没有为拓展而预留发挥的空间。因此，我们只能使用模板技术仿造progress_timer编写一个新的类：new_progress_timer，以实现任意精度的的输出。

> new_progress_timer 的实现基本复制了progress_timer的代码，他同样继承自timer，只是编程了模板类。末班参数N指明了输出的精度，默认值时2，与progress_timer相同。
