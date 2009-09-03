/*
	Aseba - an event-based framework for distributed robot control
	Copyright (C) 2007--2009:
		Stephane Magnenat <stephane at magnenat dot net>
		(http://stephane.magnenat.net)
		and other contributors, see authors.txt for details
		Mobots group, Laboratory of Robotics Systems, EPFL, Lausanne
	
	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	any other version as decided by the two original authors
	Stephane Magnenat and Valentin Longchamp.
	
	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.
	
	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "tree.h"
#include "../utils/FormatableString.h"
#include <cstdlib>

namespace Aseba
{
	/** \addtogroup compiler */
	/*@{*/
	
	std::string Node::typeName(const Node::ReturnType& type) const
	{
		switch (type)
		{
			case TYPE_UNIT: return "unit"; 
			case TYPE_BOOL: return "bool";
			case TYPE_INT: return "integer";
			default: abort(); return "unknown";
		}
	}
	
	void Node::expectType(const Node::ReturnType& expected, const Node::ReturnType& type) const
	{
		if (type != expected)
			throw Error(sourcePos, FormatableString("Expecting %0 type, found %1 type instead").arg(typeName(expected)).arg(typeName(type)));
	};
	
	Node::ReturnType Node::typeCheck() const
	{
		for (NodesVector::const_iterator it = children.begin(); it != children.end(); ++it)
		{
			(*it)->typeCheck();
		}
		return TYPE_UNIT;
	}
	
	Node::ReturnType IfWhenNode::typeCheck() const
	{
		BinaryArithmeticNode* operation = dynamic_cast<BinaryArithmeticNode*>(children[0]);
		if ((operation == 0) || (operation->op < ASEBA_OP_EQUAL))
			throw Error(children[0]->sourcePos, FormatableString("Expecting a condition, found a %0 instead").arg(children[0]->toNodeName()));
		return TYPE_UNIT;
	}
	
	Node::ReturnType WhileNode::typeCheck() const
	{
		BinaryArithmeticNode* operation = dynamic_cast<BinaryArithmeticNode*>(children[0]);
		if ((operation == 0) || (operation->op < ASEBA_OP_EQUAL))
			throw Error(children[0]->sourcePos, FormatableString("Expecting a condition, found a %0 instead").arg(children[0]->toNodeName()));
		return TYPE_UNIT;
	}
	
	Node::ReturnType BinaryArithmeticNode::typeCheck() const
	{
		switch (op)
		{
			case ASEBA_OP_SHIFT_LEFT:
			case ASEBA_OP_SHIFT_RIGHT:
			case ASEBA_OP_ADD:
			case ASEBA_OP_SUB:
			case ASEBA_OP_MULT:
			case ASEBA_OP_DIV:
			case ASEBA_OP_MOD:
			case ASEBA_OP_BIT_OR:
			case ASEBA_OP_BIT_XOR:
			case ASEBA_OP_BIT_AND:
				expectType(TYPE_INT, children[0]->typeCheck());
				expectType(TYPE_INT, children[1]->typeCheck());
				return TYPE_INT;
			
			case ASEBA_OP_EQUAL:
			case ASEBA_OP_NOT_EQUAL:
			case ASEBA_OP_BIGGER_THAN:
			case ASEBA_OP_BIGGER_EQUAL_THAN:
			case ASEBA_OP_SMALLER_THAN:
			case ASEBA_OP_SMALLER_EQUAL_THAN:
				expectType(TYPE_INT, children[0]->typeCheck());
				expectType(TYPE_INT, children[1]->typeCheck());
				return TYPE_BOOL;
			
			case ASEBA_OP_OR:
			case ASEBA_OP_AND:
				expectType(TYPE_BOOL, children[0]->typeCheck());
				expectType(TYPE_BOOL, children[1]->typeCheck());
				return TYPE_BOOL;
				
			default:
				abort();
				return TYPE_UNIT;
		}
	}
	
	Node::ReturnType UnaryArithmeticNode::typeCheck() const
	{
		switch (op)
		{
			case ASEBA_UNARY_OP_SUB:
			case ASEBA_UNARY_OP_ABS:
			case ASEBA_UNARY_OP_BIT_NOT:
				expectType(TYPE_INT, children[0]->typeCheck());
				return TYPE_INT;
			
			case ASEBA_UNARY_OP_NOT:
				expectType(TYPE_BOOL, children[0]->typeCheck());
				return TYPE_BOOL;
			
			default:
				abort();
				return TYPE_UNIT;
		}
	}
	
	/*@}*/
	
}; // Aseba

