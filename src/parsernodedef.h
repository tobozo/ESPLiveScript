
#include <string>
#include "tokenizer.h"
#pragma once
using namespace std;

/*
Helper functions
*/

/*
fin helper fiunctiopns
*/
int stack_size = 0;
int for_if_num = 0;
int block_statement_num = 0;
int nb_argument=0;
list<int> nb_args;
list<string> _header;
list<string> _content;
int point_regnum=4;
bool isExternal = false;
list<int> _register_numl;
list<int> _register_numr;
list<int> _sp;

class StackPosition
{
    public:
 StackPosition(list<list<string>::iterator> *l2)
 {
    l=l2;
 }
 void push(list<string>::iterator a)
 {
    l->push_back(a);
 }
 list<string>::iterator pop()
 {
    list<string>::iterator  sav=l->back();
    l->pop_back();
    return sav;
 }
 void clear()
 {
    l->clear();
 }
 list<string>::iterator  get()
 {
    return l->back();
 }
 void duplicate()
 {
    l->push_back(l->back());
 }
 list<list<string>::iterator> *l;


void swap()
{
    list<string>::iterator  sav=pop();
    list<string>::iterator sav2=pop();
    push(sav);
    push(sav2);
}
};







class StackInt
{
    public:
 StackInt(list<int> *l2)
 {
    l=l2;
 }
 void push(int a)
 {
    l->push_back(a);
 }
 int pop()
 {
    int sav=l->back();
    l->pop_back();
    return sav;
 }
 void clear()
 {
    l->clear();
 }
 int get()
 {
    return l->back();
 }
 void duplicate()
 {
    l->push_back(l->back());
 }
 list<int> *l;
void displaystack()
{
    int i=1;
    //printf("****DISPLAY STACK******\n");
    for(int g:*l)
    {
        //printf("%2d:%3d\n",i,g);
        i++;
    }
     //printf("****DISPLAY STACK END******\n");
}

void displaystack(string s)
{
    int i=1;
    //printf("****DISPLAY STACK %s******\n",s.c_str());
    for(int g:*l)
    {
        //printf("%2d:%3d\n",i,g);
        i++;
    }
     //printf("****DISPLAY STACK END %s******\n",s.c_str());
}
void increase()
{
    int sav=pop();
    push(sav+1);
}
void decrease()
{
    int sav=pop();
    push(sav-1);
}
void swap()
{
    int sav=pop();
    int sav2=pop();
    push(sav);
    push(sav2);
}

};



class IteratorString
{
public:
    IteratorString(list<string> *l2){
        l=l2;
        position=0;
       
    }
    void addAfter(int pos,string s)
    {
        list<string>::iterator __it=getChildAtPos(pos);
        //printf(" on recupere %d:%s\n",pos,(*__it).c_str());
        l->insert(next(__it),s);
        _it=getChildAtPos(position);
        position++;
    }
    void addAfter(string s)
    {
        _it=l->insert(next(_it),s);
        position++;
    }
        void addBefore(string s)
    {
        _it=l->insert(_it,s);
    }
        void addBefore(list<string>::iterator it,string s)
    {
        l->insert(it,s);
        _it++;
    }
    int get()
    {
        //printf("position %d: %s\n",position,(*_it).c_str());

        return position-1;
    }
    list<string>::iterator getChildAtPos(int pos)
    {
        int i = 0;
        if (pos >= l->size() || pos < 0)
        {
            return l->end();
        }
        for (list<string>::iterator it = l->begin(); it != l->end(); it++)
        {
            if (i == pos)
            {

                return it;
            }
            i++;
        }
        return l->end();
    }
    void begin()
    {
        
       _it = l->begin();
       position=0;
       
    }
    void putIteratorAtPos(int pos)
    {
         _it=getChildAtPos(pos);
    }
    void end()
    {
        _it=getChildAtPos(l->size()-1);
    }
list<string> *l;
list<string>::iterator _it;
list<string>::iterator parent;
StackInt sp=StackInt(&_sp);

int position;
};

IteratorString content=IteratorString(&_content);
IteratorString header=IteratorString(&_header);
StackInt register_numr=StackInt(&_register_numr);
StackInt register_numl=StackInt(&_register_numl);
enum statementType
{
    statementAssignment,
    statementDeclaration,
    statementDeclarationAndAssignment,
    statementIf,
    statementElse,
    statementFor,
    statementWhile,
    statementCall,
};

string statementTypeNames[] =
    {
        "statementAssignment",
        "statementDeclaration",
        "statementDeclarationAndAssignment",
        "statementIf",
        "statementElse",
        "statementFor",
        "statementWhile",
        "statementCall",
};

enum nodeType
{
    typeNode,
    numberNode,
    binOpNode,
    unitaryOpNode,
    operatorNode,
    Program,
    globalVariableNode,
    localVariableNode,
    blockStatementNode,
    defFunctionNode,
    statementNode,
    programNode,
    assignementNode,
    comparatorNode,
    callFunctionNode,
    forNode,
    argumentNode,
    extGlobalVariableNode,
    extDefFunctionNode,
    extCallFunctionNode,
    returnArgumentNode,
    variableDeclarationNode,
    defExtFunctionNode,
    inputArgumentsNode,
    defExtGlobalVariableNode,
    defGlobalVariableNode,
    defLocalVariableNode,
    storeLocalVariableNode,
    storeGlobalVariableNode,
    storeExtGlocalVariableNode,
};

string nodeTypeNames[] =
    {
        "typeNode",
        "numberNode",
        "binOpNode",
        "unitaryOpNode",
        "operatorNode",
        "Program",
        "globalVariableNode",
        "localVariableNode",
        "blockStatementNode",
        "defFunctionNode",
        "statementNode",
        "programNode",
        "assignementNode",
        "comparatorNode",
        "callFunctionNode",
        "forNode",
        "argumentNode",
        "extGlobalVariableNode",
        "extDefFunctionNode",
        "extCallFunctionNode",
        "returnArgumentNode",
        "variableDeclarationNode",
        "defExtFunctionNode",
        "inputArgumentsNode",
        "defExtGlobalVariableNode",
        "defGlobalVariableNode",
        "defLocalVariableNode",
        "storeLocalVariableNode",
        "storeGlobalVariableNode",
        "storeExtGlocalVariableNode",
};

typedef struct
{
    int error;
    string error_message;

} f_error_struct;

typedef struct
{
    int register_numl;
    int register_numr;
    string f;
    string header;
    f_error_struct error;
    string body[10];
} prt_r;

// class Context;
uint16_t stringToInt(string str)
{
    uint16_t res;
    for (int i = 0; i < str.size(); i++)
    {
        res = 10 * res + (str[i] - 48);
    }
    return res;
}

class Context;

class NodeToken
{
public:
    NodeToken() {
        parent=NULL;
        _link=NULL;
        _token=NULL;
    }

    NodeToken(token *t)
    {
        _token = t;
    }
    NodeToken *addChild(NodeToken t)
    {
        t.parent = this;
        // t._global = _global;
        children.push_back(t);
        list<NodeToken>::iterator it = children.end();
        it--;
        return &*it;
    }
    // virtual string value();

    nodeType _nodetype;
    list<NodeToken> children;
    token *_token;
    // statementType stmttype;
    void (*visitNode)(NodeToken *nd) = NULL;
    string target;
    NodeToken *_link;
    NodeToken *parent;
    // string target;
    //  Context *cntx;
    uint8_t stack_pos = 0;
    bool isPointer = false;
    uint16_t _total_size = 1;
    NodeToken *getChildAtPos(int pos)
    {
        int i = 0;
        if (pos >= children.size() || pos < 0)
        {
            return NULL;
        }
        for (list<NodeToken>::iterator it = children.begin(); it != children.end(); ++it)
        {
            if (i == pos)
            {

                return &*it;
            }
            i++;
        }
        return NULL;
    }
};


NodeToken *current_node;

NodeToken *search_result;

list<NodeToken *> sav_token;
void copyNodeToken(NodeToken from, NodeToken *to)
{
    to->_token = from._token;
}

list<NodeToken> _functions;

class Context
{
public:
    Context()
    {
        name = " ";
    };
    list<NodeToken> functions;
    list<NodeToken> variables;
    // varTypeEnum current_varType;
    Context *parent = NULL;
    list<Context> children;
    string name;
    // Context *_global = NULL;

    Context *addChild(Context cntx)
    {

        cntx.parent = this;
        cntx.name = name + "_" + cntx.name;

        // cntx._global = _global;
        children.push_back(cntx);
        list<Context>::iterator it = children.end();
        it--;
        return &*it;
    }

    void display(string id)
    {
        // ////printf("%scontext:%s\n", id.c_str(), name.c_str());
        for (int i = 0; i < variables.size(); i++)
        {
            // ////printf("%s\t%s %s %d\n", id.c_str(), variables[i]._token.text.c_str(), nodeTypeNames[variables[i]._nodetype].c_str(), variables[i]._token._vartype.external_var);
        }
        for (int i = 0; i < children.size(); i++)
        {
            display(id + "   ");
        }
    }
    void addVariable(NodeToken nd)
    {
        nd._token->text = name + "_" + nd._token->text;
        ////printf("i have added %s \n", nd._token->text.c_str());
        variables.push_back(nd);
    }
    void addFunction(NodeToken nd)
    {
        ////printf("adding function %s\n", nd._token->text.c_str());
       // nd._token->text = name + "_" + nd._token->text;
        ////printf("adding function %s\n", nd._token->text.c_str());
        _functions.push_back(nd);
    }
    void findVariable(token *t, bool isCreation)
    {
search_result=NULL;
      // //printf("lokking for variable |%s| dans %s  already %d variables defined \n", t->text.c_str(),name.c_str(),variables.size());
        for (list<NodeToken>::iterator it = variables.begin(); it != variables.end(); ++it)
        {
          // //printf("is equalt to |%s|\n", (*it)._token->text.c_str());
            if((*it)._token!=NULL)
            {
              //  ////printf("is equalt to |%s|\n", (*it)._token->text.c_str());
                if ((*it)._token->text.compare(name + "_" + t->text) == 0)
                {
                    // //printf("varianle %s found in %s\n", t->text.c_str(),name.c_str());
                     search_result=&*it;
                    return ;
                }
            }
        }
        if (!isCreation)
        {
            Context *c_cntx=this->parent;
            while(c_cntx!=NULL)
            {
               // //printf("lokking for variable |%s| dans %s %d branches\n", t->text.c_str(),c_cntx->name.c_str(),c_cntx->variables.size());
                for (list<NodeToken>::iterator it = c_cntx->variables.begin(); it != c_cntx->variables.end(); ++it)
                {
               // //printf("is equalt to |%s|\n", (*it)._token->text.c_str());
                    if((*it)._token!=NULL)
                    {
                    //  ////printf("is equalt to |%s|\n", (*it)._token->text.c_str());
                        if ((*it)._token->text.compare(c_cntx->name + "_" + t->text) == 0)
                        {
                           // //printf("varianle %s found in %s\n", t->text.c_str(),c_cntx->name.c_str());
                            search_result=&*it;
                            return ;
                        }
                    }
                }
                c_cntx=c_cntx->parent;
            }
        }
        /*
        if(!isCreation)
        {
                //printf("no variebale found\n");
        }
        else
        {
             //printf("no variebale found we will create\n");
        }*/
        search_result=NULL;
        return ;
    }
    NodeToken *findFunction(token *t)
    {


        for (list<NodeToken>::iterator it = _functions.begin(); it != _functions.end(); ++it)
        {
            

            if ((*it)._token->text.compare( t->text) == 0)
            {
                return &*it;
            }
        }
        /*
        if (parent != NULL)
        {
            return parent->findFunction(t);
        }
       */
        return NULL;
    }
};
Context cntx = Context();
Context *current_cntx=&cntx;
typedef struct
{
    f_error_struct error;
    NodeToken _nd;
} resParse;

f_error_struct Error;

void copyPrty(NodeToken *from, NodeToken *to)
{
    if (!to->isPointer)
        to->isPointer = from->isPointer;
    to->stack_pos = from->stack_pos;
    to->_token->_vartype = from->_token->_vartype;
    to->_total_size = to->_total_size * from->_token->_vartype->_varSize;
}
/*
prt_r visitNodeProgramNode(NodeToken *nd, int register_numl, int register_numr)
{
    string f, h;
    ////printf("in programl\n");
    for (int i = 0; i < nd->children.size(); i++)
    {
        if (nd->getChildAtPos(i)->visitNode != NULL)
        {
          //  prt_r g = nd->getChildAtPos(i)->visitNode(nd->getChildAtPos(i), register_numl, register_numr);
           // f = f + g.f;
           // h = h + g.header;
        }
    }
    prt_r res;
    res.f = f;
    res.header = h;
    return res;
}
*/
void _visitNodeProgramNode(NodeToken *nd)
{
    
    //printf("in programl\n");
     content.begin();
   header.begin();
   register_numr.clear();
   register_numl.clear();
   register_numl.push(15);
   register_numr.push(15);
    for (int i = 0; i < nd->children.size(); i++)
    {
        if (nd->getChildAtPos(i)->visitNode != NULL)
        {
             nd->getChildAtPos(i)->visitNode(nd->getChildAtPos(i));
            
        }
    }

}

class NodeProgram : public NodeToken
{
public:
    NodeProgram()
    {
        _nodetype = programNode;
        _token = NULL;
        visitNode = _visitNodeProgramNode;
    }
};

NodeProgram program;

class NodeVariableDeclaration : public NodeToken
{
public:
    NodeVariableDeclaration()
    {
        _nodetype = variableDeclarationNode;
        _token = NULL;
    }
};

/*
prt_r visitNodeExtGlobalVariable(NodeToken *nd, int register_numl, int register_numr)
{
    string f = "";
    string h = "";
    prt_r res;
    ////printf("in visitNodeStoreGlocalVariable\n");
    prt_r number;
    number.f = "";
    number.header = "";
    int savreg = register_numl;
    if (nd->children.size() > 0)
    {

       // number = nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0), register_numl, register_numr);
    }
    varType *v = nd->_token->_vartype;
    int start = nd->stack_pos;
    uint8_t regnum = 1;
    if (nd->isPointer)
    {
        //start = nd->stack_pos;
        regnum = point_regnum;
    }
    string body = "";
    for (int i = 0; i < v->size; i++)
    {
        res.body[i] = string_format("%s %s%d,%s%d,%d\n", v->load[i].c_str(), v->reg_name.c_str(), register_numl, v->reg_name.c_str(), regnum, start);
       // register_numl--;
        start += v->sizes[i];
    }
    //register_numl++;
     f = string_format("movExt a%d,%s\n",point_regnum, nd->_token->text.c_str());
    if (nd->isPointer)
    {
        f=f+number.f;
        for (int i = 0; i < v->size; i++)
        {
            f = f + string_format("add a%d,a%d,a%d\n", point_regnum,point_regnum,savreg);
        }
    }

    res.f = f;
    res.header = number.header + h;
    point_regnum++;
        res.register_numl=register_numl;
    res.register_numr=register_numr;
    return res;
}
*/


void _visitNodeExtGlobalVariable(NodeToken *nd)
{
    
   // int savreg = register_numl;
    register_numl.duplicate();
    if (nd->children.size() > 0)
    {
        register_numl.duplicate();
       nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0));
       register_numl.pop();
    }
    varType *v = nd->_token->_vartype;
    int start = nd->stack_pos;
    uint8_t regnum = 1;
    if (nd->isPointer)
    {
        //start = nd->stack_pos;
        regnum = point_regnum;
    }
    string body = "";
    
    //register_numl++;
      content.addAfter(string_format("movExt a%d,%s\n",point_regnum, nd->_token->text.c_str()));
    
    if (nd->isPointer)
    {
       // f=f+number.f;
        for (int i = 0; i < v->total_size; i++)
        {
            content.addAfter(  string_format("add a%d,a%d,a%d\n", point_regnum,point_regnum,register_numl.get()));
        }
    }
    content.sp.push(content.get());
for (int i = 0; i < v->size; i++)
    {
        content.addAfter( string_format("%s %s%d,%s%d,%d\n", v->load[i].c_str(), v->reg_name.c_str(), register_numl.get(), v->reg_name.c_str(), point_regnum, start));
       // register_numl--;
        start += v->sizes[i];
        content.sp.push(content.get());
    }
    //res.f = f;
   // res.header = number.header + h;
    point_regnum++;
    register_numl.pop();
    //    res.register_numl=register_numl;
   // res.register_numr=register_numr;
    return ;
}



class NodeExtGlobalVariable : public NodeToken
{
public:
    NodeExtGlobalVariable()
    {
        _nodetype = extGlobalVariableNode;
        _token = NULL;
        visitNode=_visitNodeExtGlobalVariable;
    }
    NodeExtGlobalVariable(NodeToken nd)
    {
        _nodetype = extGlobalVariableNode;
        _token = nd._token;
        isPointer = nd.isPointer;
        _total_size = nd._total_size;
        visitNode=_visitNodeExtGlobalVariable;
    }
};

/*
prt_r visitNodeStoreExtGlobalVariable(NodeToken *nd, int register_numl, int register_numr)
{
    string f = "";
    string h = "";
    prt_r res;
    ////printf("in visitNodeStoreGlocalVariable\n");
    prt_r number;
    number.f = "";
    number.header = "";
    int savreg = register_numl;
    if (nd->children.size() > 0)
    {

      //  number = nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0), register_numl, register_numr);
    }
    varType *v = nd->_token->_vartype;
    int start = nd->stack_pos;
    uint8_t regnum = 1;
    if (nd->isPointer)
    {
        //start = nd->stack_pos;
        regnum = point_regnum;
    }
    string body = "";
    for (int i = 0; i < v->size; i++)
    {
        res.body[i] = string_format("%s %s%d,%s%d,%d\n", v->store[i].c_str(), v->reg_name.c_str(), register_numl, v->reg_name.c_str(), regnum, start);
       // register_numl--;
        start += v->sizes[i];
    }
    //register_numl++;
     f = string_format("movExt a%d,%s\n",point_regnum, nd->_token->text.c_str());
    if (nd->isPointer)
    {
        f=f+number.f;
        for (int i = 0; i < v->size; i++)
        {
            f = f + string_format("add a%d,a%d,a%d\n", point_regnum,point_regnum,savreg);
        }
    }
    if(point_regnum>4)
        point_regnum--;
    res.f = f;
    res.header = number.header + h;
        res.register_numl=register_numl;
    res.register_numr=register_numr;
    return res;
}
*/

void _visitNodeStoreExtGlobalVariable(NodeToken *nd)
{
    
   // int savreg = register_numl;
    register_numl.duplicate();
    varType *v = nd->_token->_vartype;
    int start = nd->stack_pos;
    uint8_t regnum = 1;
    if (nd->isPointer)
    {
        //start = nd->stack_pos;
        regnum = point_regnum;
    }
    string body = "";
    
    //register_numl++;
     
         for(int h=0;h<v->size-1;h++)
      {
       start+= v->sizes[h];
      }
 for (int i =v->size-1; i >=0; i--)
    {
        content.addAfter( content.sp.pop(),string_format("%s %s%d,%s%d,%d", v->store[i].c_str(), v->reg_name.c_str(), register_numl.get(), v->reg_name.c_str(), point_regnum, start));
       // register_numl--;
        start -= v->sizes[i];
       //content.sp.push(content.get());
    }
    //res.f = f;
   // res.header = number.header + h;
content.sp.push(content.get());
content.sp.swap();
content.putIteratorAtPos(content.sp.get());
content.sp.displaystack("PILE");
if (nd->children.size() > 0)
    {
        register_numl.duplicate();
       nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0));
       register_numl.pop();
    }
    
 content.addAfter(string_format("movExt a%d,%s",
 point_regnum, nd->_token->text.c_str()));
    
    if (nd->isPointer)
    {
       // f=f+number.f;
        for (int i = 0; i < v->total_size; i++)
        {
            content.addAfter(  string_format("add a%d,a%d,a%d", point_regnum,point_regnum,register_numl.get()));
        }
    }
content.end();
content.sp.pop();
    point_regnum++;
    register_numl.pop();
    point_regnum--;

    //    res.register_numl=register_numl;
   // res.register_numr=register_numr;
    return ;
}

class NodeStoreExtGlobalVariable : public NodeToken
{
public:
    NodeStoreExtGlobalVariable()
    {
        _nodetype = extGlobalVariableNode;
        _token = NULL;
        visitNode=_visitNodeStoreExtGlobalVariable;
    }
    NodeStoreExtGlobalVariable(NodeToken nd)
    {
        _nodetype = extGlobalVariableNode;
        _token = nd._token;
        isPointer = nd.isPointer;
        _total_size = nd._total_size;
        visitNode=_visitNodeStoreExtGlobalVariable;
    }
};
/*
prt_r visitNodeGlobalVariable(NodeToken *nd, int register_numl, int register_numr)
{
    string f = "";
    string h = "";
    prt_r res;
    ////printf("in visitNodeStoreGlocalVariable\n");
    prt_r number;
    number.f = "";
    number.header = "";
    int savreg = register_numl;
    if (nd->children.size() > 0)
    {

     //   number = nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0), register_numl, register_numr);
    }
    varType *v = nd->_token->_vartype;
    int start = nd->stack_pos;
    uint8_t regnum = 1;
    if (nd->isPointer)
    {
        //start = nd->stack_pos;
        regnum = point_regnum;
    }
    string body = "";
    for (int i = 0; i < v->size; i++)
    {
        res.body[i] = string_format("%s %s%d,%s%d,%d\n", v->load[i].c_str(), v->reg_name.c_str(), register_numl, v->reg_name.c_str(), regnum, start);
       // register_numl--;
        start += v->sizes[i];
    }
    //register_numl++;
     f = string_format("l32r a%d,%s\n",point_regnum, nd->_token->text.c_str());
    if (nd->isPointer)
    {
        f=f+number.f;
        for (int i = 0; i < v->size; i++)
        {
            f = f + string_format("add a%d,a%d,a%d\n", point_regnum,point_regnum,savreg);
        }
    }

    res.f = f;
    res.header = number.header + h;
    point_regnum++;
        res.register_numl=register_numl;
    res.register_numr=register_numr;
    return res;
}
*/

void _visitNodeGlobalVariable(NodeToken *nd)
{
    
   // int savreg = register_numl;
    register_numl.duplicate();
    if (nd->children.size() > 0)
    {
        register_numl.duplicate();
       nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0));
       register_numl.pop();
    }
    varType *v = nd->_token->_vartype;
    int start = nd->stack_pos;
    uint8_t regnum = 1;
    if (nd->isPointer)
    {
        //start = nd->stack_pos;
        regnum = point_regnum;
    }
    string body = "";
    
    //register_numl++;
      content.addAfter( string_format("l32r a%d,main_%s\n",point_regnum, nd->_token->text.c_str()));
    
    if (nd->isPointer)
    {
       // f=f+number.f;
        for (int i = 0; i < v->total_size; i++)
        {
            content.addAfter(  string_format("add a%d,a%d,a%d\n", point_regnum,point_regnum,register_numl.get()));
        }
    }
    content.sp.push(content.get());
for (int i = 0; i < v->size; i++)
    {
        content.addAfter( string_format("%s %s%d,%s%d,%d\n", v->load[i].c_str(), v->reg_name.c_str(), register_numl.get(), v->reg_name.c_str(), point_regnum, start));
       // register_numl--;
        start += v->sizes[i];
        content.sp.push(content.get());
    }
    //res.f = f;
   // res.header = number.header + h;
   // point_regnum++;
    register_numl.pop();
    //    res.register_numl=register_numl;
   // res.register_numr=register_numr;
   register_numl.decrease();
    return ;
    /*
if (nd->children.size() > 0)
    {

        nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0));
    }
     content.addAfter( string_format("l32r a%d,main_%s\n",point_regnum, nd->_token->text.c_str()));
          content.addAfter( string_format("mov a%d,main_%s\n",point_regnum, nd->_token->text.c_str()));
     point_regnum++;
     */
}
class NodeGlobalVariable : public NodeToken
{
public:
    NodeGlobalVariable()
    {
        _nodetype = globalVariableNode;
        _token = NULL;
       visitNode=_visitNodeGlobalVariable;
    }
    NodeGlobalVariable(NodeToken nd)
    {
        _nodetype = globalVariableNode;
        _token = nd._token;
        isPointer = nd.isPointer;
        _total_size = nd._total_size;
        visitNode=_visitNodeGlobalVariable;
    }
};

/*
prt_r visitNodeStoreGlobalVariable(NodeToken *nd, int register_numl, int register_numr)
{
    string f = "";
    string h = "";
    prt_r res;
    ////printf("in visitNodeStoreGlocalVariable\n");
    prt_r number;
    number.f = "";
    number.header = "";
    int savreg = register_numl;
    if (nd->children.size() > 0)
    {

       // number = nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0), register_numl, register_numr);
    }
    varType *v = nd->_token->_vartype;
    int start = nd->stack_pos;
    uint8_t regnum = 1;
    if (nd->isPointer)
    {
        //start = nd->stack_pos;
        regnum = point_regnum;
    }
    string body = "";
    for (int i = 0; i < v->size; i++)
    {
        res.body[i] = string_format("%s %s%d,%s%d,%d\n", v->store[i].c_str(), v->reg_name.c_str(), register_numl, v->reg_name.c_str(), regnum, start);
       // register_numl--;
        start += v->sizes[i];
    }
    //register_numl++;
     f = string_format("l32r a%d,%s\n",point_regnum, nd->_token->text.c_str());
    if (nd->isPointer)
    {
        f=f+number.f;
        for (int i = 0; i < v->size; i++)
        {
            f = f + string_format("add a%d,a%d,a%d\n", point_regnum,point_regnum,savreg);
        }
    }
    if(point_regnum>4)
        point_regnum--;
    res.f = f;
    res.header = number.header + h;
        res.register_numl=register_numl;
    res.register_numr=register_numr;
    return res;
}
*/

void _visitNodeStoreGlobalVariable(NodeToken *nd)
{
    
    
   // int savreg = register_numl;
    register_numl.duplicate();
    varType *v = nd->_token->_vartype;
    int start = nd->stack_pos;
    uint8_t regnum = 1;
    if (nd->isPointer)
    {
        //start = nd->stack_pos;
        regnum = point_regnum;
    }
    string body = "";
    
    //register_numl++;
     
         for(int h=0;h<v->size-1;h++)
      {
       start+= v->sizes[h];
      }
 for (int i =v->size-1; i >=0; i--)
    {
        content.addAfter( content.sp.pop(),string_format("%s %s%d,%s%d,%d", v->store[i].c_str(), v->reg_name.c_str(), register_numl.get(), v->reg_name.c_str(), point_regnum, start));
       // register_numl--;
        start -= v->sizes[i];
       //content.sp.push(content.get());
    }
    //res.f = f;
   // res.header = number.header + h;
content.sp.push(content.get());
content.sp.swap();
content.putIteratorAtPos(content.sp.get());
content.sp.displaystack("PILE");
if (nd->children.size() > 0)
    {
        register_numl.duplicate();
       nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0));
       register_numl.pop();
    }
    
content.addAfter( string_format("l32r a%d,main_%s\n",point_regnum, nd->_token->text.c_str()));
    
    if (nd->isPointer)
    {
       // f=f+number.f;
        for (int i = 0; i < v->total_size; i++)
        {
            content.addAfter(  string_format("add a%d,a%d,a%d", point_regnum,point_regnum,register_numl.get()));
        }
    }
content.end();
content.sp.pop();
    point_regnum++;
    register_numl.pop();
    point_regnum--;

    //    res.register_numl=register_numl;
   // res.register_numr=register_numr;
    return ;
}

class NodeStoreGlobalVariable : public NodeToken
{
public:
    NodeStoreGlobalVariable()
    {
        _nodetype = storeGlobalVariableNode;
        _token = NULL;
        visitNode = _visitNodeStoreGlobalVariable;
    }
    NodeStoreGlobalVariable(NodeToken nd)
    {
        _nodetype = storeGlobalVariableNode;
        _token = nd._token;
        isPointer = nd.isPointer;
        _total_size = nd._total_size;
        visitNode = _visitNodeStoreGlobalVariable;
    }
};

/*
prt_r visitNodeLocalVariable(NodeToken *nd, int register_numl, int register_numr)
{
    string f = "";
    string h = "";
    prt_r res;
    ////printf("in visitNodeStoreLocalVariable\n");
    prt_r number;
    number.f = "";
    number.header = "";
    int savreg = register_numl;
    if (nd->children.size() > 0)
    {

      //  number = nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0), register_numl, register_numr);
    }
    varType *v = nd->_token->_vartype;
    int start = nd->stack_pos;
    uint8_t regnum = 1;
    if (nd->isPointer)
    {
        //start = nd->stack_pos;
        regnum = point_regnum;
    }
    string body = "";
    for (int i = 0; i < v->size; i++)
    {
        res.body[i] = string_format("%s %s%d,%s%d,%d\n", v->load[i].c_str(), v->reg_name.c_str(), register_numl, v->reg_name.c_str(), regnum, start);
       // register_numl--;
        start += v->sizes[i];
    }
   // register_numl++;
    if (nd->isPointer)
    {
        for (int i = 0; i < v->size; i++)
        {
            f = f + string_format("add a%d,a%d,a%d\n",point_regnum,point_regnum, savreg);
        }
    }
    //point_regnum--;
    res.f = f;
    res.header = number.header + h;
    res.register_numl=register_numl-1;
    res.register_numr=register_numr;
    return res;
}
*/

void _visitNodeLocalVariable(NodeToken *nd)
{

   register_numl.duplicate();
   // if (nd->children.size() > 0)
    //{

      //  number = nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0), register_numl, register_numr);
   // }
    varType *v = nd->_token->_vartype;
    int start = nd->stack_pos;
    uint8_t regnum = 1;
    if (nd->isPointer)
    {
        //start = nd->stack_pos;
        regnum = point_regnum;
    }
    


  for (int i = 0; i < v->size; i++)
    {
         content.addAfter(string_format("%s %s%d,%s%d,%d", v->load[i].c_str(), v->reg_name.c_str(), register_numl.get(), v->reg_name.c_str(), regnum, start));
       // register_numl--;
        start += v->sizes[i];
        content.sp.push(content.get());
    }
   // register_numl++;
 //  content.sp.push(content.get());
//content.sp.swap();
//content.putIteratorAtPos(content.sp.get());
content.sp.displaystack("PILE");
if (nd->children.size() > 0)
    {
        register_numl.duplicate();
       nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0));
       register_numl.pop();
    }

    if (nd->isPointer)
    {
        for (int i = 0; i < v->total_size; i++)
        {
            content.addAfter(  string_format("add a%d,a%d,a%d", point_regnum,point_regnum,register_numl.get()));
        }
    }
    //point_regnum--;

   // content.end();
//content.sp.pop();
register_numl.pop();
register_numl.decrease();

    return ;
}




class NodeLocalVariable : public NodeToken
{
public:
    NodeLocalVariable()
    {
        _nodetype = localVariableNode;
        _token = NULL;
       visitNode=_visitNodeLocalVariable;
    }
    NodeLocalVariable(NodeToken nd)
    {
        _nodetype = localVariableNode;
        _token = nd._token;
        isPointer = nd.isPointer;
        _total_size = nd._total_size;
        stack_pos = nd.stack_pos;
        visitNode=_visitNodeLocalVariable;
    }
};
/*
prt_r visitNodeStoreLocalVariable(NodeToken *nd, int register_numl, int register_numr)
{
    string f = "";
    string h = "";
    prt_r res;
    ////printf("in visitNodeStoreLocalVariable\n");
    prt_r number;
    number.f = "";
    number.header = "";
    int savreg = register_numl;
    if (nd->children.size() > 0)
    {

      // number = nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0), register_numl, register_numr);
    }
    varType *v = nd->_token->_vartype;
    int start = nd->stack_pos;
    uint8_t regnum = 1;
    if (nd->isPointer)
    {
        //start = nd->stack_pos;
        regnum = point_regnum;
    }
    string body = "";
    for (int i = 0; i < v->size; i++)
    {
        res.body[i] = string_format("%s %s%d,%s%d,%d\n", v->store[i].c_str(), v->reg_name.c_str(), register_numl, v->reg_name.c_str(), regnum, start);
       // register_numl--;
        start += v->sizes[i];
    }
   // register_numl++;
    if (nd->isPointer)
    {
        for (int i = 0; i < v->size; i++)
        {
            f = f + string_format("add a%d,a%d,a%d\n",point_regnum,point_regnum, savreg);
        }
    }
    //point_regnum--;
    res.f = f;
    res.header = number.header + h;
        res.register_numl=register_numl;
    res.register_numr=register_numr;
    return res;
}
*/



void _visitNodeStoreLocalVariable(NodeToken *nd)
{
    //printf("jjjkkj\n");
    varType *v = nd->_token->_vartype;
    uint8_t regnum = 1;
     int start = nd->stack_pos;
 int numl=register_numl.get();
     for(int h=0;h<v->size-1;h++)
      {
       start+= v->sizes[h];
      }
    for (int i =v->size-1; i >=0; i--)
    {
      //printf("jjjkkj: %d\n",i);
     // list<string>::iterator l=content.sp.pop();
 
       content.addAfter(  content.sp.pop(),  string_format("%s %s%d,%s%d,%d", v->store[i].c_str(), v->reg_name.c_str(), numl, v->reg_name.c_str(), regnum, start));
      
     // numl++;
        start -= v->sizes[i];
    }

}
class NodeStoreLocalVariable : public NodeToken
{
public:
    NodeStoreLocalVariable()
    {
        _nodetype = storeLocalVariableNode;
        _token = NULL;
       visitNode = _visitNodeStoreLocalVariable;
    }
    NodeStoreLocalVariable(NodeToken nd)
    {
        _nodetype = storeLocalVariableNode;
        _token = nd._token;
        isPointer = nd.isPointer;
        _total_size = nd._total_size;
        stack_pos = nd.stack_pos;
        visitNode = _visitNodeStoreLocalVariable;
    }
};
/*
prt_r visitNodeDefExtGlobalVariable(NodeToken *nd, int register_numl, int register_numr)
{
    string f = "";
    string h = "";
    ////printf("in visitNodeDefExtGlobalVariable\n");
    prt_r res;
    res.f = f;
    res.header = h;
        res.register_numl=register_numl;
    res.register_numr=register_numr;
    return res;
}
*/

class NodeDefExtGlobalVariable : public NodeToken
{
public:
    NodeDefExtGlobalVariable()
    {
        _nodetype = defExtGlobalVariableNode;
        _token = NULL;
       // visitNode = visitNodeDefExtGlobalVariable;
    }
    NodeDefExtGlobalVariable(NodeToken nd)
    {
        _nodetype = defExtGlobalVariableNode;
        _token = nd._token;
        isPointer = nd.isPointer;
        _total_size = nd._total_size;
       // visitNode = visitNodeDefExtGlobalVariable;
    }
};
/*
prt_r visitNodeDefGlobalVariable(NodeToken *nd, int register_numl, int register_numr)
{
    ////printf("in visitNodeDefGlobalVariable\n");
    string f = "";
    string h = "";
    h = string_format("%s:\n.bytes %d\n", nd->_token->text.c_str(), nd->_total_size);
    prt_r res;
    res.f = f;
    res.header = h;
        res.register_numl=register_numl;
    res.register_numr=register_numr;
    return res;
}
*/

void _visitNodeDefGlobalVariable(NodeToken *nd)
{
    ////printf("in visitNodeDefGlobalVariable\n");
    string f = "";
    string h = "";
    header.addAfter( string_format("%s:\n.bytes %d", nd->_token->text.c_str(), nd->_total_size));
    
    return ;
}

class NodeDefGlobalVariable : public NodeToken
{
public:
    NodeDefGlobalVariable()
    {
        _nodetype = defGlobalVariableNode;
        _token = NULL;
        visitNode = _visitNodeDefGlobalVariable;
    }
    NodeDefGlobalVariable(NodeToken nd)
    {
        _nodetype = defGlobalVariableNode;
        _token = nd._token;
        isPointer = nd.isPointer;
        _total_size = nd._total_size;
        visitNode = _visitNodeDefGlobalVariable;
    }
};
/*
prt_r visitNodeDefLocalVariable(NodeToken *nd, int register_numl, int register_numr)
{
    ////printf("in visitNodeDefGlobalVariable\n");
    string f = "";
    string h = "";
  //  h = string_format("%s:\n.bytes %d\n", nd->_token->text.c_str(), nd->_total_size);
    prt_r res;
    res.f = f;
    res.header = h;
        res.register_numl=register_numl;
    res.register_numr=register_numr;
    return res;
}
*/


class NodeDefLocalVariable : public NodeToken
{
public:
    NodeDefLocalVariable()
    {
        _nodetype = defLocalVariableNode;
        _token = NULL;
       // visitNode=visitNodeDefLocalVariable;
    }
    NodeDefLocalVariable(NodeToken nd)
    {
        _nodetype = defLocalVariableNode;

        isPointer = nd.isPointer;
        _total_size = nd._total_size;
       // visitNode=visitNodeDefLocalVariable;
        int delta = 0;
        if (nd._token->_vartype->_varType == __unit32_t__  || nd._token->_vartype->_varType == __float__)
        {
            if (stack_size % 4 != 0)
                delta = nd._token->_vartype->_varSize - stack_size % 4;
        }
        else if (nd._token->_vartype->_varType == __unit16_t__ ||nd._token->_vartype->_varType == __int__)
        {
            if (stack_size % 2 != 0)
            {
                delta = 1;
            }
        }
        stack_size += delta;
        nd.stack_pos = stack_size;
        stack_size += nd._token->_vartype->_varSize;
        _token = nd._token;
        stack_pos = nd.stack_pos;
    }
};


void _visitNodeCallFunction(NodeToken *nd)
{
    /*
        prt_r r;

            NodeToken *ds=nd->_link;
            for(int i=0;i<ds->getChildAtPos(1)->children.size();i++)
            {
                r.f=r.f+nodeTypeNames[  ds->getChildAtPos(1)->getChildAtPos(i)->_nodetype].c_str();
            }
            r.f=string_format("callExt a15,%s\n",nd->_token->text.c_str());
                r.register_numl=register_numl;
    r.register_numr=register_numr;
        return r;
        */
       content.addAfter(string_format("mov a10,a2\nmov a11,a3"));
       content.addAfter(string_format("call8 %s\n",nd->_token->text.c_str()));


}


class NodeCallFunction : public NodeToken
{
public:
    NodeCallFunction()
    {
        _nodetype = callFunctionNode;
        _token = NULL;
        visitNode = _visitNodeCallFunction;
    }
    NodeCallFunction(token *t)
    {
        _token = t;
        _nodetype = callFunctionNode;
         visitNode = _visitNodeCallFunction;
    }
    NodeCallFunction(NodeToken *t)
    {
        //_token = t->_token;
        _token = t->_token;
        ;
        _nodetype = callFunctionNode;
        _link = t;

        visitNode = _visitNodeCallFunction;
    }
};

/*
prt_r visitNodeExtCallFunction(NodeToken *nd, int register_numl, int register_numr)
{
        prt_r r;

             NodeToken *t =nd->_link;// cntx.findFunction(nd->_token);
            if(t==NULL)
            {
               
                return r;
            }
            ////printf(" %s %d %d\n",nd->_token->text.c_str(),  t->children.size(),t->getChildAtPos(1)->children.size());
            
            for(int i=0;i<t->getChildAtPos(1)->children.size();i++)
            {
               // prt_r argin=nd->getChildAtPos(0)->getChildAtPos(i)->visitNode(nd->getChildAtPos(0)->getChildAtPos(i), register_numl, register_numr);
               // r.header=r.header+argin.header;
               // r.f=r.f+argin.f;
                ////printf("xxxx :%d %s\n",nd->getChildAtPos(0)->getChildAtPos(i)->_token->_vartype->size,argin.body[0].c_str());
                for(int j=0;j<nd->getChildAtPos(0)->getChildAtPos(i)->_token->_vartype->size;j++)
                {
                  //  r.f=r.f+argin.body[j];
                }

                r.f=r.f+string_format("mov a%d,a%d\n",10+i,register_numl);
            }
            
            r.f=r.f+string_format("callExt a15,%s\n",nd->_token->text.c_str());
        
    r.register_numl=register_numl;
    r.register_numr=register_numr;
        return r;
}
*/

void _visitNodeExtCallFunction(NodeToken *nd)
{
       

             NodeToken *t =nd->_link;// cntx.findFunction(nd->_token);
            if(t==NULL)
            {
               
                return ;
            }
            //printf(" %s %d %d\n",nd->_token->text.c_str(),  t->children.size(),t->getChildAtPos(1)->children.size());
            
            for(int i=0;i<t->getChildAtPos(1)->children.size();i++)
            {
                register_numl.duplicate();
                nd->getChildAtPos(0)->getChildAtPos(i)->visitNode(nd->getChildAtPos(0)->getChildAtPos(i));
                //r.header=r.header+argin.header;
               // r.f=r.f+argin.f;
              //  //printf("xxxx :%d %s\n",nd->getChildAtPos(0)->getChildAtPos(i)->_token->_vartype->size,argin.body[0].c_str());
                /*
                for(int j=0;j<nd->getChildAtPos(0)->getChildAtPos(i)->_token->_vartype->size;j++)
                {
                    r.f=r.f+argin.body[j];
                }
                */
               register_numl.pop();
                content.addAfter(string_format ("mov a%d,a%d",10+i,register_numl.get()));
            }
            
            content.addAfter( string_format("callExt a15,%s",nd->_token->text.c_str()));
            int start = nd->stack_pos;
            varType *v = nd->_link->getChildAtPos(0)->_token->_vartype;
for(int i=0;i<v->size;i++)
{
   content.addAfter(string_format("mov a15,a10"));
       // register_numl--;
        start += v->sizes[i];
        content.sp.push(content.get());
}
        return ;
}

class NodeExtCallFunction : public NodeToken
{
public:
    NodeExtCallFunction()
    {
        _nodetype = extCallFunctionNode;
        _token = NULL;
        visitNode = _visitNodeExtCallFunction;
    }
    NodeExtCallFunction(token *t)
    {
        _token = t;
        _nodetype = extCallFunctionNode;
        visitNode = _visitNodeExtCallFunction;
    }
    NodeExtCallFunction(NodeToken *t)
    {
        //_token = t->_token;
        _token = t->_token;
        _nodetype = extCallFunctionNode;
        _link = t;
         visitNode = _visitNodeExtCallFunction;
    }
};
/*
prt_r visitNodeDefFunction(NodeToken *nd, int register_numl, int register_numr)
{
    ////printf("in visitNodeFunctionNode\n");
    string f = "";
    string h = "";
    h = string_format(".global %s\n", nd->_token->text.c_str());
    f = string_format("%s: \nentry a1,%d\n", nd->_token->text.c_str(), ((nd->stack_pos) / 4 + 1) * 4);
    for (int i = 0; i < nd->children.size(); i++)
    {
        if (nd->getChildAtPos(i)->visitNode != NULL)
        {
           // prt_r g = nd->getChildAtPos(i)->visitNode(nd->getChildAtPos(i), register_numl, register_numr);
           // f = f + g.f;
           // h = h + g.header;
        }
        
    }

    f = f + string_format("retw.n\n");
    prt_r res;
    res.f = f;
    res.header = h;
        res.register_numl=register_numl;
    res.register_numr=register_numr;
    return res;
}
*/
void _visitNodeDefFunction(NodeToken *nd)
{
    ////printf("in visitNodeFunctionNode\n");
    //string f = "";
    //string h = "";

    header.addAfter (string_format(".global %s", nd->_token->text.c_str()));
    
   
     content.addAfter(  string_format("%s: \nentry a1,%d", nd->_token->text.c_str(),80)); // ((nd->stack_pos) / 8 + 1) * 8)
    for (int i = 0; i < nd->children.size(); i++)
    {
        if (nd->getChildAtPos(i)->visitNode != NULL)
        {
           nd->getChildAtPos(i)->visitNode(nd->getChildAtPos(i));
           // f = f + g.f;
           // h = h + g.header;
        }
        
    }
 content.addAfter ( string_format("retw.n"));
   // prt_r res;
   // res.f = f;
    //res.header = h;
      //  res.register_numl=register_numl;
    //res.register_numr=register_numr;
    //return res;
}


class NodeDefFunction : public NodeToken
{
public:
    NodeDefFunction()
    {
        _nodetype = defFunctionNode;
        _token = NULL;
       visitNode = _visitNodeDefFunction;
    }
    NodeDefFunction(token *t)
    {
        _token = t;
        _nodetype = defFunctionNode;
        visitNode = _visitNodeDefFunction;
    }
    NodeDefFunction(NodeToken t)
    {
        _token = t._token;
        _nodetype = defFunctionNode;
        visitNode = _visitNodeDefFunction;
    }
};
/*
prt_r visitNodeDefExtFunction(NodeToken *nd, int register_numl, int register_numr)
{
    ////printf("in visitNodeDefExtFunction\n");
    string f = "";
    string h = "";

    prt_r res;
    res.f = f;
    res.header = h;
        res.register_numl=register_numl;
    res.register_numr=register_numr;
    
    return res;
}
*/
class NodeDefExtFunction : public NodeToken
{
public:
    NodeDefExtFunction()
    {
        _nodetype = defExtFunctionNode;
        _token = NULL;
       // visitNode = visitNodeDefExtFunction;
    }
    NodeDefExtFunction(token *t)
    {
        _token = t;
        _nodetype = defExtFunctionNode;
      //  visitNode = visitNodeDefExtFunction;
    }
    NodeDefExtFunction(NodeToken t)
    {
        _token = t._token;
        _nodetype = defExtFunctionNode;
      //  visitNode = visitNodeDefExtFunction;
    }
};

class NodeInputArguments : public NodeToken
{
public:
    NodeInputArguments()
    {
        _nodetype = inputArgumentsNode;
        _token = NULL;
        // visitNode = visitNodeFunctionNode;
    }
    NodeInputArguments(token *t)
    {
        _token = t;
        _nodetype = inputArgumentsNode;
        _token = NULL;
        // visitNode = visitNodeFunctionNode;
    }
};

/*
prt_r visitNodeBlockStatement(NodeToken *nd, int register_numl, int register_numr)
{
    string f, h;
    ////printf("in visitNodeBlockStatement\n");
    for (int i = 0; i < nd->children.size(); i++)
    {
        if (nd->getChildAtPos(i)->visitNode != NULL)
        {
          //  prt_r g = nd->getChildAtPos(i)->visitNode(nd->getChildAtPos(i), register_numl, register_numr);
           // f = f + g.f;
           // h = h + g.header;
        }
    }
    prt_r res;
    res.f = f;
    res.header = h;
        res.register_numl=register_numl;
    res.register_numr=register_numr;
    return res;
}
*/

void _visitNodeBlockStatement(NodeToken *nd)
{
    //printf("in block statement");
    for (int i = 0; i < nd->children.size(); i++)
    {
        if (nd->getChildAtPos(i)->visitNode != NULL)
        {
          nd->getChildAtPos(i)->visitNode(nd->getChildAtPos(i));
           // f = f + g.f;
           // h = h + g.header;
        }
    }
}

class NodeBlockStatement : public NodeToken
{
public:
    NodeBlockStatement()
    {
        _nodetype = blockStatementNode;
        _token = NULL;
        visitNode = _visitNodeBlockStatement;
    }
    NodeBlockStatement(token *t)
    {
        _token = t;
        _nodetype = blockStatementNode;
       visitNode = _visitNodeBlockStatement;
    }
};

/*
prt_r visitNodeOperator(NodeToken *nd,  int register_numl, int register_numr)
{
    string f;
    prt_r r;
    ////printf("operator %s\n",tokenNames[nd->_token->type].c_str());
    switch (nd->_token->type)
    {
    case TokenAddition:
        r.f = string_format("add a%d,a%d,a%d\n", register_numl, register_numl, register_numr);
        r.register_numr = register_numr;
        r.register_numl = register_numl;
        return r;
        break;
    case TokenStar:
        r.register_numr = register_numr;
        r.register_numl = register_numl;
        r.f = string_format("mull a%d,a%d,a%d\n", register_numl, register_numl, register_numr);
        return r;
        break;
    default:

        r.f = "Unknown\n";
        return r;
        break;
    }
}
*/

void _visitNodeOperator(NodeToken *nd)
{

    //printf("operator %s\n",tokenNames[nd->_token->type].c_str());
    //register_numl.pop();
    register_numl.displaystack();
    switch (nd->_token->type)
    {
    case TokenAddition:
        content.addAfter( string_format("add a%d,a%d,a%d", register_numl.get(), register_numl.get(), register_numr.get()));

        return ;
        break;
    case TokenSubstraction:
        content.addAfter( string_format("sub a%d,a%d,a%d", register_numl.get(), register_numl.get(), register_numr.get()));

        return ;
        break;      
            case TokenSlash:
        content.addAfter( string_format("quou a%d,a%d,a%d", register_numl.get(), register_numl.get(), register_numr.get()));

        return ;
        break;    
    case TokenStar:

        content.addAfter(string_format("mull a%d,a%d,a%d", register_numl.get(), register_numl.get(), register_numr.get()));
        return ;
  break;
    case TokenModulo:

        content.addAfter(string_format("remu a%d,a%d,a%d", register_numl.get(), register_numl.get(), register_numr.get()));
        return ;
        break;   

    default:
        return ;
        break;
    }
}

class NodeOperator : public NodeToken
{
public:
    NodeOperator()
    {
        _nodetype = operatorNode;
        _token = NULL;
         visitNode = _visitNodeOperator;
    }
    NodeOperator(token *t)
    {
        _nodetype = operatorNode;
        _token = t;
        visitNode = _visitNodeOperator;
    }
};


 

/*

prt_r visitNodeBinOperator(NodeToken *nd,  int register_numl, int register_numr)
{
    string f = "";
    prt_r fleft;
    prt_r fright;
    prt_r f1;
   // if (nd->getChildAtPos(0)->visitNode != NULL)
       // fleft = nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0),  register_numl, register_numr);
   // if (nd->getChildAtPos(2)->visitNode != NULL)
       // fright = nd->getChildAtPos(2)->visitNode(nd->getChildAtPos(2),  fleft.register_numl, fleft.register_numr);
   // if (nd->getChildAtPos(1)->visitNode != NULL)
       // f1 = nd->getChildAtPos(1)->visitNode(nd->getChildAtPos(1),  register_numl, fleft.register_numl);

    prt_r r;
//    r.f = fleft.body[0]+fleft.f + fright.body[0]+fright.f + f1.f;
 //   r.header=fleft.header + fright.header + f1.header;
 //   r.register_numl = fright.register_numl;
   // if (nd->getChildAtPos(1)->_token->type == TokenAddition || nd->getChildAtPos(1)->_token->type == TokenSubstraction )
   //     r.register_numl += 1;

    //r.register_numr = fright.register_numr;

    return r;
}
*/


void _visitNodeBinOperator(NodeToken *nd)
{
    //printf("bin operator\n");
    register_numl.displaystack();
   register_numl.duplicate();
  // register_numr.duplicate();
     if (nd->getChildAtPos(0)->visitNode != NULL)
            nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0));
 register_numl.displaystack();
 register_numl.duplicate();
  //register_numr.duplicate();
 if (nd->getChildAtPos(2)->visitNode != NULL)
 nd->getChildAtPos(2)->visitNode(nd->getChildAtPos(2));
//register_numr.pop();
 register_numl.swap();
 register_numr.push(register_numl.pop());
register_numl.swap();

 register_numl.displaystack();

  if (nd->getChildAtPos(1)->visitNode != NULL)
  nd->getChildAtPos(1)->visitNode(nd->getChildAtPos(1));
   register_numl.pop();
   if (nd->getChildAtPos(1)->_token->type == TokenAddition || nd->getChildAtPos(1)->_token->type == TokenSubstraction )
   {
       register_numl.increase();
   }
   content.sp.pop();
   content.sp.pop();
   content.sp.push(content.get());
   //register_numl.pop();
   
  register_numr.pop();
  // register_numr.pop();



}
class NodeBinOperator : public NodeToken
{
public:
    NodeBinOperator(NodeToken left, NodeOperator t, NodeToken right)
    {
        children.push_back(left);
        children.push_back(t);
        children.push_back(right);
        _nodetype = binOpNode;
        _token = NULL;
         visitNode = _visitNodeBinOperator;
    }
    NodeBinOperator()
    {
        _nodetype = binOpNode;
        _token = NULL;
         visitNode = _visitNodeBinOperator;
    }
};
class NodeUnitary : public NodeToken
{
public:
    NodeUnitary(NodeOperator t, NodeToken right)
    {
        children.push_back(t);
        children.push_back(right);
        _nodetype = unitaryOpNode;
        _token = NULL;
    }
        NodeUnitary()
    {

        _nodetype = unitaryOpNode;
        _token = NULL;
    }
            NodeUnitary(NodeOperator t)
    {
children.push_back(t);
        _nodetype = unitaryOpNode;
        _token = NULL;
    }

};

/*

prt_r visitNodeNumber(NodeToken *nd, int register_numl, int register_numr)
{
    prt_r r;
    string f = "";
    if (nd->children.size() > 0)
    {
        for (int i = 0; i < nd->children.size(); i++)
        {
           // prt_r temp = nd->getChildAtPos(i)->visitNode(nd->getChildAtPos(i), register_numl, register_numl);
           // r.body[i] = temp.f;
        }
    }
    else
    {
        f = f + string_format("movi a%d,%s\n", register_numl, nd->_token->text.c_str());
    }

    r.f = f;
    r.header = "";
    r.register_numl = register_numl - 1;
    r.register_numr = register_numr;
    return r;
}
*/

void _visitNodeNumber(NodeToken *nd)
{
    //printf("in number\n");
register_numl.displaystack();
    // register_numl.duplicate();
    

if (nd->children.size() > 0)
    {
        
       
        for (int i = 0; i < nd->children.size(); i++)
        {
            register_numl.duplicate();
            nd->getChildAtPos(i)->visitNode(nd->getChildAtPos(i));
             //register_numl.pop();
           //content.sp.push(content.get());
          register_numl.pop();
        }
       
        
    }
    else
    {
        //register_numl.pop();
       // register_numl.pop();
        content.addAfter(string_format("movi a%d,%s", register_numl.get(), nd->_token->text.c_str()));
        content.sp.push(content.get());
        register_numl.decrease();
            //printf("exit number\n");
register_numl.displaystack();
    }
        
         
   // register_numr.push(register_numl.get()+1);
  //register_numl.pop();

}
class NodeNumber : public NodeToken
{
public:
    NodeNumber(token *t)
    {
        _token = t;
        _nodetype = numberNode;
       visitNode = _visitNodeNumber;
    }
};

NodeToken createNodeVariable(token *_var, NodeToken *nd, bool isStore)
{
    //////printf("***************create cariavbla %d %s\n", isStore ,nodeTypeNames[nd->_nodetype].c_str());
    NodeToken var = NodeToken(_var);
    switch (nd->_nodetype)
    {
    case extGlobalVariableNode:
    {
        
        if (isStore)
        {
            NodeStoreExtGlobalVariable v = NodeStoreExtGlobalVariable(var);
            copyPrty(nd, &v);
            return v;
        }
        else
        {
            NodeExtGlobalVariable v = NodeExtGlobalVariable(var);
            copyPrty(nd, &v);
            return v;
        }
    }
    break;
        case defExtGlobalVariableNode:
    {
        
        if (isStore)
        {
            NodeStoreExtGlobalVariable v = NodeStoreExtGlobalVariable(var);
            copyPrty(nd, &v);
            return v;
        }
        else
        {
            NodeExtGlobalVariable v = NodeExtGlobalVariable(var);
            copyPrty(nd, &v);
            return v;
        }
    }
    break;
        case defLocalVariableNode:
    {
       
        if (isStore == true)
        {
            NodeStoreLocalVariable v = NodeStoreLocalVariable(var);
            copyPrty(nd, &v);
            return v;
        }
        else
        {
            NodeLocalVariable v = NodeLocalVariable(var);
            copyPrty(nd, &v);
            return v;
        }
    }
    break;
    case localVariableNode:
    {
       
        if (isStore == true)
        {
            NodeStoreLocalVariable v = NodeStoreLocalVariable(var);
            copyPrty(nd, &v);
            return v;
        }
        else
        {
            NodeLocalVariable v = NodeLocalVariable(var);
            copyPrty(nd, &v);
            return v;
        }
    }
    break;
    case defGlobalVariableNode:
    {
       
        if (isStore)
        {
            NodeStoreGlobalVariable v = NodeStoreGlobalVariable(var);
            copyPrty(nd, &v);
            return v;
        }
        else
        {
            NodeGlobalVariable v = NodeGlobalVariable(var);
            copyPrty(nd, &v);
            return v;
        }
    }
    break;    
    case globalVariableNode:
    {
       
        if (isStore)
        {
            NodeStoreGlobalVariable v = NodeStoreGlobalVariable(var);
            copyPrty(nd, &v);
            return v;
        }
        else
        {
            NodeGlobalVariable v = NodeGlobalVariable(var);
            copyPrty(nd, &v);
            return v;
        }
    }
    break;
    default:
    {
        
        if (isStore)
        {
            NodeStoreLocalVariable v = NodeStoreLocalVariable(var);
            copyPrty(nd, &v);
            return v;
        }
        else
        {
            NodeLocalVariable v = NodeLocalVariable(var);
            copyPrty(nd, &v);
            return v;
        }
    }
    break;
    }
}

NodeToken createNodeLocalVariableForCreation(NodeToken *var, NodeToken *nd)
{
    ////printf("smldfksdlfklmskflsdkf %d\n",nd->isPointer);
    switch (var->_nodetype)
    {
    case defGlobalVariableNode:
    {
        
        NodeDefGlobalVariable v = NodeDefGlobalVariable(*var);
copyPrty(nd, &v);
        return v;
    }
    break;
    case defLocalVariableNode:
    {

       // copyPrty(*nd, var);
        NodeDefLocalVariable v = NodeDefLocalVariable(*var);
copyPrty(nd, &v);
        return v;
    }
    break;

        break;
    default:
    {

        copyPrty(nd, var);
        NodeDefLocalVariable v = NodeDefLocalVariable(*var);

        return v;
    }
    break;
    }
}

NodeToken createNodeLocalVariableForStore(NodeToken var)
{
   // ////printf("111&&&&&&&&&&&qssdqsdqsd& %s\n",nodeTypeNames[var._nodetype].c_str());
    switch (var._nodetype)
    {
    case defGlobalVariableNode:
    {
       // copyPrty(*nd, var);
        NodeStoreGlobalVariable v = NodeStoreGlobalVariable(var);

        return v;
    }
    break;
    case defLocalVariableNode:
    {

       // copyPrty(*nd, var);
        NodeStoreLocalVariable v = NodeStoreLocalVariable(var);

        return v;
    }
    break;

        break;
    default:
    {

       // copyPrty(*nd, var);
        NodeStoreLocalVariable v = NodeStoreLocalVariable(var);

        return v;
    }
    break;
    }
}

/*
prt_r visitNodeAssignement(NodeToken *nd, int register_numl, int register_numr)
{
    //////printf("in visitNodeAssignement %d\n", nd->getChildAtPos(0)->_token->_vartype->size);
    string f = "";
    string h = "";
    prt_r right;
    prt_r left;

    if (nd->getChildAtPos(1)->visitNode != NULL)
    {
        right = nd->getChildAtPos(1)->visitNode(nd->getChildAtPos(1), register_numl, register_numr);
    }
    if (nd->getChildAtPos(0)->visitNode != NULL)
    {
        left = nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0), register_numl, register_numr);
    }

    prt_r res;
    res.f = f + left.f+ right.f ;
    string midlle="";
    for (int i = 0; i < nd->getChildAtPos(0)->_token->_vartype->size; i++)
    {
        midlle = midlle + right.body[i] + left.body[i];
    }
    res.f=res.f+midlle;
    res.header = h + right.header + left.header;
        res.register_numl=register_numl;
    res.register_numr=register_numr;
    return res;
}
*/

void _visitNodeAssignement(NodeToken *nd)
{
    //printf("in Assignment Node\n");
    point_regnum=4;
    content.sp.push(content.get());
   register_numl.duplicate();
 content.sp.displaystack("PILE");
    if (nd->getChildAtPos(1)->visitNode != NULL)
    {
        register_numl.duplicate();
        nd->getChildAtPos(1)->visitNode(nd->getChildAtPos(1));
        register_numl.pop();
    }
    content.sp.displaystack("PILE");
    //printf("before store\n");
    register_numl.displaystack();
  // register_numl.pop();
    //register_numl.displaystack();
        if (nd->getChildAtPos(0)->visitNode != NULL)
    {
        register_numl.duplicate();
         nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0));
          register_numl.pop();
        
    }
    register_numl.pop();
    content.sp.pop();
}

class NodeAssignement : public NodeToken
{
public:
    NodeAssignement()
    {
        _nodetype = assignementNode;
        _token = NULL;
        visitNode = _visitNodeAssignement;
    }
    NodeAssignement(token *t)
    {
        _nodetype = assignementNode;
        _token = t;
        visitNode = _visitNodeAssignement;
    }
};

/*
prt_r visitNodeStatement(NodeToken *nd, int register_numl, int register_numr)
{
    string f, h;
    ////printf("in visitNodeStatement\n");
    for (int i = 0; i < nd->children.size(); i++)
    {
        if (nd->getChildAtPos(i)->visitNode != NULL)
        {
          //  prt_r g = nd->getChildAtPos(i)->visitNode(nd->getChildAtPos(i), register_numl, register_numr);
            f = f + g.f;
            h = h + g.header;
        }
    }
    prt_r res;
    res.f = f;
    res.header = h;
        res.register_numl=register_numl;
    res.register_numr=register_numr;
    return res;
}*/
void visitNodeStatement(NodeToken *nd)
{
    point_regnum=4;
   
    for (int i = 0; i < nd->children.size(); i++)
    {
        if (nd->getChildAtPos(i)->visitNode != NULL)
        {
            register_numl.duplicate();
           nd->getChildAtPos(i)->visitNode(nd->getChildAtPos(i));
          register_numl.pop();
        }
    }

    return;
}
class NodeStatement : public NodeToken
{
public:
    NodeStatement()
    {
        _nodetype = statementNode;
        _token = NULL;
        visitNode = visitNodeStatement;
    }
    NodeStatement(token *t)
    {
        _nodetype = statementNode;
        _token = t;
       visitNode = visitNodeStatement;
    }
};

/*
prt_r visitNodeFor(NodeToken *nd,  int register_numl, int register_numr)
{
     prt_r r;
     prt_r start;
     prt_r compar;
     prt_r inc;
     prt_r block;

     
        if (nd->getChildAtPos(0)->visitNode != NULL)
        start = nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0),  register_numl, register_numr);
        if (nd->getChildAtPos(1)->visitNode != NULL)
        compar =nd->getChildAtPos(1)->visitNode(nd->getChildAtPos(1), register_numl, register_numr);
        if (nd->getChildAtPos(2)->visitNode != NULL)
        inc = nd->getChildAtPos(2)->visitNode(nd->getChildAtPos(2),  register_numl, register_numr);
        if (nd->getChildAtPos(3)->visitNode != NULL)
        block = nd->getChildAtPos(3)->visitNode(nd->getChildAtPos(3),  register_numl, register_numr);


        r.header=start.header+compar.header+inc.header+block.header;
        r.f=start.f+nd->target+":\n"+block.f+inc.f+compar.f;
    r.register_numl=register_numl;
    r.register_numr=register_numr;
     return r;
}
*/
void _visitNodeFor(NodeToken *nd)
{


     
        if (nd->getChildAtPos(0)->visitNode != NULL)
        {
            register_numl.duplicate();
         nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0));
         register_numl.pop();
        }
        content.addAfter(string_format("%s:",nd->target.c_str()));
        if (nd->getChildAtPos(3)->visitNode != NULL)
        {
             register_numl.duplicate();
        nd->getChildAtPos(3)->visitNode(nd->getChildAtPos(3));
         register_numl.pop();
        }

    if (nd->getChildAtPos(2)->visitNode != NULL)
    {
        register_numl.duplicate();
        nd->getChildAtPos(2)->visitNode(nd->getChildAtPos(2));
        register_numl.pop();
    }


        if (nd->getChildAtPos(1)->visitNode != NULL)
        {
            register_numl.duplicate();
         nd->getChildAtPos(1)->visitNode(nd->getChildAtPos(1));
         register_numl.pop();
        }
    



       // r.header=start.header+compar.header+inc.header+block.header;
       // r.f=start.f+nd->target+":\n"+block.f+inc.f+compar.f;
    //r.register_numl=register_numl;
   // r.register_numr=register_numr;
     return ;
}

class NodeFor : public NodeToken
{
public:
    NodeFor()
    {
        _token = NULL;

        _nodetype = forNode;
        visitNode = _visitNodeFor;
    };

    NodeFor(token *t) // token th
    {
        // children.push_back(right);
        // children.push_back(right);
        _token = t;

        _nodetype = forNode;
        //_token._keyword = th._keyword;

        visitNode = _visitNodeFor;
    }
};

/*

prt_r visitNodeComparatorFunction(NodeToken *nd, int register_numl, int register_numr)
{
    string f = "";
    prt_r fleft;
    prt_r fright;
    prt_r f1;
    if (nd->getChildAtPos(0)->visitNode != NULL)
        fleft = nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0), register_numl, register_numr);
    if (nd->getChildAtPos(1)->visitNode != NULL)
        fright = nd->getChildAtPos(1)->visitNode(nd->getChildAtPos(1),  fleft.register_numl, fleft.register_numr);
        
////printf("compare %s %s\n",tokenNames[nd->_token->type ].c_str(),nd->_token->text.c_str());
    switch(nd->_token->type)
    {
        case TokenLessThan:
            f=string_format("bge a%d,a%d,%s_end\n",register_numl,fleft.register_numl,nd->target.c_str());
            f=f+string_format("j %s\n",nd->target.c_str());
            f=f+string_format("%s_end:\n",nd->target.c_str());
        break;
        default:
        break;        
    }

    prt_r r;
    r.f = fleft.f + fright.f + f;
    r.header=fleft.header+fright.header;

    r.register_numl = fright.register_numl;

        r.register_numl += 1;

    r.register_numr = fright.register_numr;

    return r;
}
*/

void _visitNodeComparatorFunction(NodeToken *nd)
{
    string f = "";
    prt_r fleft;
    prt_r fright;
    prt_r f1;
    int numl=register_numl.get();
    if (nd->getChildAtPos(0)->visitNode != NULL)
        nd->getChildAtPos(0)->visitNode(nd->getChildAtPos(0));
        int leftl=register_numl.get();
    if (nd->getChildAtPos(1)->visitNode != NULL)
        nd->getChildAtPos(1)->visitNode(nd->getChildAtPos(1));
        
////printf("compare %s %s\n",tokenNames[nd->_token->type ].c_str(),nd->_token->text.c_str());
    switch(nd->_token->type)
    {
        case TokenLessThan:
           content.addAfter( string_format("bge a%d,a%d,%s_end\n",numl,leftl,nd->target.c_str()));
            content.addAfter(  string_format("j %s\n",nd->target.c_str()));
              content.addAfter( string_format("%s_end:\n",nd->target.c_str()));
        break;
        default:
        break;        
    }
/*
    prt_r r;
    r.f = fleft.f + fright.f + f;
    r.header=fleft.header+fright.header;

    r.register_numl = fright.register_numl;

        r.register_numl += 1;

    r.register_numr = fright.register_numr;
    */
   register_numl.increase();

    return ;
}

class NodeComparator : public NodeToken
{
public:
    NodeComparator()
    {
        _token = NULL;
        _nodetype = comparatorNode;
        visitNode=_visitNodeComparatorFunction;
    };

    NodeComparator(token *t) // token th
    {
        // children.push_back(right);
        // children.push_back(right);
        _token = t;
        //_token.text = _token.text;
        _nodetype = comparatorNode;
        //_token._keyword = th._keyword;

        visitNode = _visitNodeComparatorFunction;
    }
};

void clearContext(Context *cntx)
{
    ////printf("clearContect\n");
    for (list<Context>::iterator it = cntx->children.begin(); it != cntx->children.end(); ++it)
        {
                clearContext(&*it);

        }
       cntx->functions.clear() ;
         cntx->variables.clear();
         cntx->children.clear();
         /*
         if(cntx->parent!=NULL)
         {
            ////printf("on delete cntx %s\n",cntx->name.c_str());
             free(cntx);
         }*/
}

void clearNodeToken(NodeToken *nd)
{
    ////printf("clearNodeToke\n");

   // nd->children.clear();
   // return;
    /*
    //printf("on efface %s",nodeTypeNames[nd->_nodetype].c_str());
    if(nd->_token!=NULL)
    {
        
        //printf("\t %s\n",nd->_token->text.c_str());
    }
    else
    {
        //printf("\n");
    }
    */
   _functions.clear();
    for (list<NodeToken>::iterator it = nd->children.begin(); it != nd->children.end(); ++it)
        {
            if(&*it!=NULL)
                clearNodeToken(&*it);

        }
        /*
        if(nd->_token!=NULL)
        {
            ////printf("on try le delete \n");
                delete nd->_token;
        }*/
     nd->children.clear();
     
     /*
        if(nd->parent!=NULL)
        {
         ////printf("on delete NodeToken \n");
         delete nd;
        }
        */
}