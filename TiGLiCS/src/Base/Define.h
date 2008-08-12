#pragma once

#include "Base/Base.h"
#include "Objects/Object.h"
#include <set>
#include <list>
namespace TiGLiCS{
	namespace Object{
		struct ProcessPriorityComparison{
			bool operator () (const CObjectContainer * left,const CObjectContainer * right)const{
				return left->pObj->GetProcessPriority() < right->pObj->GetProcessPriority(); 
			}
		};

		struct PtrPriorityComparison{//íœ—p
			bool operator () (const CObjectContainer * left,const CObjectContainer * right)const{
				return ((left->pObj) < (right->pObj)); 
			}
		};
		typedef std::multiset<CObjectContainer *,ProcessPriorityComparison> ProcessPriorityList;
		
		typedef std::set<CObjectContainer *,PtrPriorityComparison> PtrPriorityList;

	}

}