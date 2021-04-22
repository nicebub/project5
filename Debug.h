#ifndef _DEBUG_H
#define _DEBUG_H

namespace ucc{
	class Debug{
		public:
			Debug();
			~Debug();
			static int get_yydebug() ;
			static void set_yydebug(const int value);
		private:
			static int yydebug;
	};
}

#endif