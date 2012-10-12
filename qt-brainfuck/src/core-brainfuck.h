
#ifndef __CORE_BRAINFUCK_H__
#define __CORE_BRAINFUCK_H__

#include <QVector>
#include <QMap>
#include <QString>
#include <iostream>

namespace brainfuck
{
	class input
	{
		public:
			virtual void get(QChar &ch) = 0;
	};

	class output
	{
		public:
			virtual void put(QChar ch) = 0;
	};

	class command
	{
		public:
			command(int nAddress, QVector<brainfuck::command*>&) 
			: 
				m_nAddress(nAddress), 
				m_nNextAddress(nAddress+1)
			{
			};
			
			void setNextAddress(int nNextAddress) { m_nNextAddress = nNextAddress; };
			int getNextAddress() { return m_nNextAddress; };
			int getAddress() { return m_nAddress; };

			virtual void exec(QVector<int> &, int &, int &nCursorInCode)
			{
				if( nCursorInCode != m_nAddress)
					std::cout << "\n error in address " << m_nAddress << " \n";
			};

		private:
			int m_nAddress;
			int m_nNextAddress;
	};
	
	class creator_command
	{
		public:
			virtual brainfuck::command * create(int nAddress, QVector<brainfuck::command*> &vStackWithCommandReturn) = 0;
	};

	#define CREATOR_( creator_classname, command_classname) \
	class creator_classname : public brainfuck::creator_command \
	{ \
		virtual brainfuck::command * create(int nAddress, QVector<brainfuck::command*> &vStackWithCommandReturn) \
		{ \
			return new command_classname(nAddress, vStackWithCommandReturn); \
		}; \
	};

	class core
	{
		public:
			core();
			// void clear();
			void execute();
			void add_command(QChar ch);
			bool check_command(QChar ch);

		private:

			QMap<QChar, creator_command* > m_vInterpret;

			QVector<brainfuck::command*> m_vCode;
			QVector<brainfuck::command*> m_vStackWithCommandReturn;
			QVector<int> m_vMemory;
			int m_nCursorInMemory;
			int m_nCursorInCode;
	};
}

#endif // __CORE_BRAINFUCK_H__
