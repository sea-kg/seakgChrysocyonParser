#include "core-brainfuck.h"
#include <cstdio>
// ------------------------------------------------
class command_incr : public brainfuck::command
{
	public: 
		command_incr(int nAddress, QVector<brainfuck::command*> &vStackWithCommandReturn) 
		: 
			command::command(nAddress, vStackWithCommandReturn)
		{
							
		};

		virtual void exec(QVector<int> &vMemory, int &nCursorInMemory, int &nCursorInCode)
		{
			// std::cout << "addr: " << nCursorInCode << "; command: '+' addr in memory: "<< nCursorInMemory << " \n";						
			command::exec(vMemory, nCursorInMemory, nCursorInCode);

			if(nCursorInMemory < vMemory.size())
			{
				//std::cout << "addr: " << nCursorInCode << "; command: '+' addr in memory: "<< nCursorInMemory << " \n";
				vMemory[nCursorInMemory]++;
			}

			nCursorInCode = command::getNextAddress();
		};
};
// ------------------------------------------------

class command_decr : public brainfuck::command
{
	public: 
		command_decr(int nAddress, QVector<brainfuck::command*> &vStackWithCommandReturn) 
		: 
			command::command(nAddress, vStackWithCommandReturn)
		{
							
		};
		virtual void exec(QVector<int> &vMemory, int &nCursorInMemory, int &nCursorInCode)
		{
			// std::cout << "addr: " << nCursorInCode << "; command: '-' addr in memory: "<< nCursorInMemory << " \n";
			command::exec(vMemory, nCursorInMemory, nCursorInCode);
			if(nCursorInMemory < vMemory.size())
				vMemory[nCursorInMemory]--;

			nCursorInCode = command::getNextAddress();
		};
};

// ------------------------------------------------

class command_get : public brainfuck::command
{
	public: 
		command_get(int nAddress, QVector<brainfuck::command*> &vStackWithCommandReturn) 
		: 
			command::command(nAddress, vStackWithCommandReturn)
		{
			
		};
		virtual void exec(QVector<int> &vMemory, int &nCursorInMemory, int &nCursorInCode)
		{
			command::exec(vMemory, nCursorInMemory, nCursorInCode);
			if(nCursorInMemory < vMemory.size())
			{
				char ch = std::getchar();
				vMemory[nCursorInMemory] = ch;
			}

			nCursorInCode = command::getNextAddress();
		};
};

// ------------------------------------------------

class command_put : public brainfuck::command
{
	public: 
		command_put(int nAddress, QVector<brainfuck::command*> &vStackWithCommandReturn) 
		: 
			command::command(nAddress, vStackWithCommandReturn)
		{
			
		};
		virtual void exec(QVector<int> &vMemory, int &nCursorInMemory, int &nCursorInCode)
		{
			// std::cout << "addr: " << nCursorInCode << "; command: ',' addr in memory: "<< nCursorInMemory << " \n";
			command::exec(vMemory, nCursorInMemory, nCursorInCode);
			if(nCursorInMemory < vMemory.size())
			{
				std::cout << char(vMemory[nCursorInMemory]);
				//std::cout << char(vMemory[nCursorInMemory]) << "; code=" << vMemory[nCursorInMemory] << "\n";
			}

			nCursorInCode = command::getNextAddress();
		};
};

// ------------------------------------------------

class command_next : public brainfuck::command
{
	public: 
		command_next(int nAddress, QVector<brainfuck::command*> &vStackWithCommandReturn) 
		: 
			command::command(nAddress, vStackWithCommandReturn)
		{
			
		};

		virtual void exec(QVector<int> &vMemory, int &nCursorInMemory, int &nCursorInCode)
		{
			// std::cout << "addr: " << nCursorInCode << "; command: '>' addr in memory: "<< nCursorInMemory << " \n";
			command::exec(vMemory, nCursorInMemory, nCursorInCode);
	
			if(vMemory.size() <= nCursorInMemory+1)
				vMemory.push_back(0);
			nCursorInMemory++;

			nCursorInCode = command::getNextAddress();
		};
};

// ------------------------------------------------

class command_prev : public brainfuck::command
{
	public: 
		command_prev(int nAddress, QVector<brainfuck::command*> &vStackWithCommandReturn) 
		: 
			command::command(nAddress, vStackWithCommandReturn)
		{
				
		};

		virtual void exec(QVector<int> &vMemory, int &nCursorInMemory, int &nCursorInCode)
		{
			// std::cout << "addr: " << nCursorInCode << "; command: '<' addr in memory: "<< nCursorInMemory << " \n";
			command::exec(vMemory, nCursorInMemory, nCursorInCode);
			nCursorInMemory--;
			
			if(nCursorInMemory < 0 )
				nCursorInMemory = 0;

			nCursorInCode = command::getNextAddress();
		};
};

// ------------------------------------------------

class command_begin_while : public brainfuck::command
{
	public: 
		command_begin_while(int nAddress, QVector<brainfuck::command*> &vStackWithCommandReturn) : command::command(nAddress, vStackWithCommandReturn)
		{
			vStackWithCommandReturn.push_front(this);
		};

		virtual void exec(QVector<int> &vMemory, int &nCursorInMemory, int &nCursorInCode)
		{
			command::exec(vMemory, nCursorInMemory, nCursorInCode);
			
			nCursorInCode = command::getNextAddress();
		};
};

// ------------------------------------------------

class command_end_while : public brainfuck::command
{
	public: 

		command_end_while(int nAddress, QVector<brainfuck::command*> &vStackWithCommandReturn) 
		: 
				command::command(nAddress, vStackWithCommandReturn)
		{
			
			if(vStackWithCommandReturn.size() > 0)
			{
				command::setNextAddress(vStackWithCommandReturn[0]->getAddress());
				vStackWithCommandReturn.pop_front();
			}
			else
				std::cout << "\n error not found '[' \n";
		};

		virtual void exec(QVector<int> &vMemory, int &nCursorInMemory, int &nCursorInCode)
		{
			command::exec(vMemory, nCursorInMemory, nCursorInCode);
			
			if(nCursorInMemory < vMemory.size())
			{
				int nValueOfMemory = vMemory[nCursorInMemory];
				if( nValueOfMemory != 0)
					nCursorInCode = command::getNextAddress();
				else 
					nCursorInCode = command::getAddress() + 1;
			}
			else
				std::cout << "\n error out of memory \n";
		};
};

class command_info : public brainfuck::command
{
	public: 

		command_info(int nAddress, QVector<brainfuck::command*> &vStackWithCommandReturn) 
		: 
				command::command(nAddress, vStackWithCommandReturn)
		{
		};

		virtual void exec(QVector<int> &vMemory, int &nCursorInMemory, int &nCursorInCode)
		{
			command::exec(vMemory, nCursorInMemory, nCursorInCode);
			
			std::cout << "info: [code_addr=" << nCursorInCode << "][mem_addr=" << nCursorInMemory << "]";
			if(nCursorInMemory < vMemory.size())
			{
				int nValueOfMemory = vMemory[nCursorInMemory];
				std::cout << "[valueofmemory=" << nValueOfMemory << "]";
			}

			std::cout << "\n";

			nCursorInCode = command::getNextAddress();
		};	 
};

// ------------------------------------------------

CREATOR_(creator_com_incr, command_incr)
CREATOR_(creator_com_decr, command_decr)
CREATOR_(creator_com_get, command_get)
CREATOR_(creator_com_put, command_put)
CREATOR_(creator_com_next, command_next)
CREATOR_(creator_com_prev, command_prev)
CREATOR_(creator_com_begin_while, command_begin_while)
CREATOR_(creator_com_end_while, command_end_while)
CREATOR_(creator_com_info, command_info)

namespace brainfuck
{
	core::core()
	{
		
		m_vInterpret.insert('+', new creator_com_incr() );
		m_vInterpret.insert('-', new creator_com_decr() );
		m_vInterpret.insert(',', new creator_com_get() );
		m_vInterpret.insert('.', new creator_com_put() );
		m_vInterpret.insert('>', new creator_com_next() );
		m_vInterpret.insert('<', new creator_com_prev() );
		m_vInterpret.insert('[', new creator_com_begin_while() );
		m_vInterpret.insert(']', new creator_com_end_while() );
		m_vInterpret.insert('i', new creator_com_info() );
	};



	bool core::check_command(QChar ch)
	{
		brainfuck::creator_command *p = m_vInterpret.value(ch, 0);
		return (p != 0);
	};

	void core::add_command(QChar ch)
	{
		brainfuck::creator_command *p = m_vInterpret.value(ch, 0);
		if(p != 0)
		{
			brainfuck::command *pCommand = p->create(m_vCode.size(), m_vStackWithCommandReturn);
			m_vCode.push_back(pCommand);
		};
	};


	void core::execute()
	{
		int nAddress = 0;
		m_nCursorInMemory = 0;	
		m_vMemory.clear();
		m_vMemory.push_back(0);

		int nBeforeAddress;
		while( nAddress < m_vCode.size() && nAddress >= 0)
		{
			nBeforeAddress = nAddress;
			m_vCode[nAddress]->exec(m_vMemory, m_nCursorInMemory, nAddress);
			//std::cout << nAddress << "\n";
			if(nAddress == nBeforeAddress || nAddress > m_vCode.size())
				return;
		};
	};

}
