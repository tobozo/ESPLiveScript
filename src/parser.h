#include <vector>
#include <string>
// #include "tokenizer.h"
#ifndef  __TEST_DEBUG
#include "asm_parser.h"
#endif

#pragma once
using namespace std;

#include "parsernodedef.h"

class Parser
{

public:
    NodeToken root;
    Parser() {}

    string linepos()
    {
        string f = string_format(" at line:%d pos:%d", current()->line, current()->pos);
        return f;
    }
    int size()
    {
        return _tks.size();
    }
    token *getTokenAtPos(int pos)
    {
        return _tks.getTokenAtPos(pos);
    }
    token *current()
    {
        return _tks.current();
    }
    token *next()
    {
        return _tks.next();
    }
    token *prev()
    {
        return _tks.prev();
    }
    token *peek(int index)
    {
        return _tks.peek(index);
    }
    bool Match(tokenType tt)
    {
        return _tks.Match(tt);
    }
    bool Match(tokenType tt, int index)
    {
        return _tks.Match(tt, index);
    }
    bool MatchKeyword(KeywordType t)
    {
        return _tks.MatchKeyword(t);
    }
    bool MatchKeyword(KeywordType t, int offset)
    {
        return _tks.MatchKeyword(t, offset);
    }

    void parse()
    {
        root._nodetype = programNode;
        point_regnum = 4;
        stack_size = 0;
        for_if_num = 0;
        block_statement_num = 0;
        local_var_num=0;
        nb_argument = 0;
        _tks.init();
        current_cntx = &cntx;
        parseProgram();
    }
    void clean()
    {
        clearContext(&cntx);
        clearNodeToken(&program);
        list_of_token.clear();
        nb_args.clear();
    }
    void cleanint()
    {
        clearContext(current_cntx);
        clearNodeToken(&program);
    }
    void clean2()
    {
        _header.clear();
        _content.clear();
        _sp.clear();
        _target_stack.clear();
        _register_numr.clear();
        _register_numl.clear();
        _node_token_stack.clear();
    }

    void parseCreateArguments()
    {
        Error.error = 0;
        NodeInputArguments arg;
        current_node = current_node->addChild(arg);
        if (Match(TokenCloseParenthesis))
        {
            // resParse result;
            Error.error = 0;
            // result._nd = arg;
            current_node = current_node->parent;
            // printf("on retourne with argh ide\n");
            return;
        }
        parseType();
        if (Error.error)
        {
            return;
        }
        parseVariableForCreation();
        if (Error.error)
        {
            return;
        }
        NodeToken _nd = nodeTokenList.pop();
        NodeToken t = nodeTokenList.pop();

        copyPrty(&t, &_nd);
        NodeDefLocalVariable var = NodeDefLocalVariable(_nd);

        // copyPrty(type._nd,&var);
        current_node->addChild(var);
        current_cntx->addVariable(var);
        // arg.addChild(nd);
        // next();
        // printf("current %s\n", tokenNames[current()->type].c_str());
        while (Match(TokenComma))
        {
            next();
            parseType();
            if (Error.error)
            {
                return;
            }
            parseVariableForCreation();
            if (Error.error)
            {
                return;
            }
            NodeToken _nd = nodeTokenList.pop();
            NodeToken t = nodeTokenList.pop();
            copyPrty(&t, &_nd);
            NodeDefLocalVariable var = NodeDefLocalVariable(_nd);

            // arg.addChild(var);
            current_node->addChild(var);
            current_cntx->addVariable(var);
            // next();
        }
        // prev();
        // resParse result;
        Error.error = 0;
        current_node = current_node->parent;
        return;
    }

    void getVariable(bool isStore)
    {

        current_cntx->findVariable(current(), false); // false
        // NodeToken *nd = search_result;
        if (search_result == NULL)
        {
            // //printf("hhheeheh\n");

            Error.error = 1;
            Error.error_message = string_format("impossible to find declaraiton for %s %s", current()->text.c_str(), linepos().c_str());
            next();
            return;
        }
        else
        {
            // token *vartoken = current();
            // auto var =
            // current_node = current_node->addChild(
            createNodeVariable(current(), search_result, isStore);
            next();
            if (Match(TokenOpenBracket))
            {
                // on parse
                next();

                parseExpr();
                if (Error.error)
                {
                    next();
                    return;
                }

                if (Match(TokenCloseBracket))
                {

                    // var.addChild(expr._nd);
                    // resParse res;
                    Error.error = 0;
                    current_node = current_node->parent;
                    // res._nd = var;
                    next();
                    return;
                }
                else
                {

                    Error.error = 1;
                    Error.error_message = string_format("expecting ] %s", current()->text.c_str());
                    next();
                    return;
                }
            }
            else
            {

                Error.error = 0;
                current_node = current_node->parent;
                // res._nd = var;
                // next();
                return;
            }
        }
    }

    void parseFactor()
    {
        // resParse result;
        Error.error = 0;
        // printf("entering factor line:%d pos:%d\n",current()->line,current()->pos);
        token *_f = current();
        if (_f->type == TokenEndOfFile)
        {

            next();
            return;
        }

        else if (Match(TokenNumber))
        {

            next();
            NodeNumber g = NodeNumber(_f);
            Error.error = 0;
            // result._nd = g;
            // printf("exit factor\n");
            current_node->addChild(g);
            return;
        }

        else if (Match(TokenAddition) || Match(TokenSubstraction))
        {
            // token *t = current();
            NodeUnitary g = NodeUnitary();
            current_node = current_node->addChild(g);
            current_node->addChild(NodeOperator(current()));
            next();

            parseFactor();
            if (Error.error == 1)
            {
                return;
            }
            // NodeUnitary g = NodeUnitary(NodeOperator(t), res._nd);
            Error.error = 0;
            return;
        }

        else if (Match(TokenOpenParenthesis))
        {
            next();
            parseExpr();
            if (Error.error == 1)
            {
                return;
            }
            // NodeToken d=parseExpr();
            if (Match(TokenCloseParenthesis))
            {
                next();
                Error.error = 0;
                return;
            }
        }

        else if (Match(TokenIdentifier) && !Match(TokenOpenParenthesis, 1))
        {
            getVariable(false);
            if (Error.error == 1)
            {
                // next();
                return;
            }

            return;
        }

        else if (Match(TokenIdentifier) && Match(TokenOpenParenthesis, 1))
        {
            return parseFunctionCall();
        }

        else if (Match(TokenKeyword) && MatchKeyword(KeywordVarType) && Match(TokenOpenParenthesis, 1))
        {
            // on tente CRGB()
            token *typeVar = current();
            NodeNumber num = NodeNumber(typeVar);
            current_node = current_node->addChild(num);
            next();
            if (Match(TokenOpenParenthesis))
            {
                for (int i = 0; i < typeVar->_vartype->size; i++)
                {
                    next();
                    parseExpr();
                    if (Error.error)
                    {
                        next();
                        return;
                    }
                    // num.addChild(res._nd);
                    if (i == typeVar->_vartype->size - 1)
                    {
                        if (!Match(TokenCloseParenthesis))
                        {
                            // resParse res;
                            Error.error = 1;
                            Error.error_message = string_format(" ecpected  ) %s", linepos().c_str());
                            next();
                            return;
                        }
                    }
                    else
                    {
                        if (!Match(TokenComma))
                        {
                            // resParse res;
                            Error.error = 1;
                            Error.error_message = string_format(" ecpected  , %s", linepos().c_str());
                            next();
                            return;
                        }
                    }
                }
                next();
                current_node = current_node->parent;
                // resParse result;
                Error.error = 0;

                // result._nd=num;
                return;
            }
            else
            {
                // resParse res;
                Error.error = 1;
                Error.error_message = string_format(" ecpected ( %s", linepos().c_str());
                next();
                return;
            }
        }

        Error.error = 1;
        next();
        Error.error_message = "impossible to find";

        return;
    }

    void parseTerm()
    {
        // printf("entering term line:%d pos:%d\n",current()->line,current()->pos);
        // NodeToken *sav_pa = current_node;
        sav_token.push_back(current_node);
        parseFactor();
        if (Error.error)
        {
            return;
        }
        while (Match(TokenStar) || Match(TokenSlash) || Match(TokenModulo))
        {
            token *op = current();

            next();
            NodeBinOperator nodeopt;

            NodeToken d = current_node->children.back();
            current_node->children.pop_back();
            current_node = current_node->addChild(nodeopt);
            current_node->addChild(d);

            // current_node->parent->children.remove(current_node->parent->children.back());
            NodeOperator opt = NodeOperator(op);
            current_node->addChild(opt);
            parseFactor();
            if (Error.error == 1)
            {
                return;
            }
            current_node = current_node->parent;
            // left._nd = NodeBinOperator(left._nd, opt, right._nd);
        }
        // next();
        current_node = sav_token.back();
        sav_token.pop_back();
        // current_node = sav_pa;
        // printf("exit term\n");
        return;
    }

    void parseExpr()
    {
        // NodeToken *sav_pa = current_node;
        sav_token.push_back(current_node);
        parseTerm();
        if (Error.error == 1)
        {
            return;
        }
        while (Match(TokenAddition) || Match(TokenSubstraction))
        {

            token *op = current();

            next();
            NodeBinOperator nodeopt;

            NodeToken d = current_node->children.back();
            current_node->children.pop_back();
            current_node = current_node->addChild(nodeopt);
            current_node->addChild(d);

            // current_node->parent->children.remove(current_node->parent->children.back());
            NodeOperator opt = NodeOperator(op);
            current_node->addChild(opt);
            parseTerm();
            if (Error.error == 1)
            {
                return;
            }
            current_node = current_node->parent;
            // left._nd = NodeBinOperator(left._nd, opt, right._nd);
        }
        // next();
        current_node = sav_token.back();
        sav_token.pop_back();
        // current_node = sav_pa;
        // printf("exit expr");
        Error.error = 0;
        return;
    }

    void parseArguments()
    {
        // resParse result;
        nb_argument = 0;
        nb_args.push_back(0);
        NodeInputArguments arg;
        current_node = current_node->addChild(arg);
        if (Match(TokenCloseParenthesis))
        {
            // resParse result;
            Error.error = 0;
            // result._nd = arg;
            // printf("on retourne with argh ide\n");
            current_node = current_node->parent;
            next();
            return;
        }
        nb_args.pop_back();
        nb_args.push_back(1);
        nb_argument = 1;
        parseExpr();
        if (Error.error)
        {
            return;
        }
        // arg.addChild(res._nd);
        while (Match(TokenComma))
        {
            next();
            int sav = nb_args.back();
            nb_args.pop_back();
            nb_args.push_back(sav + 1);
            nb_argument++;
            parseExpr();
            if (Error.error)
            {
                return;
            }
            // arg.addChild(res._nd);
        }
        if (!Match(TokenCloseParenthesis))
        {

            Error.error = 1;
            Error.error_message = string_format("Expected ) %s", linepos().c_str());
            next();
            return;
        }
        next();
        Error.error = 0;
        // result._nd = arg;
        current_node = current_node->parent;
        return;
    }

    void parseFunctionCall()
    {
        int sav_nb_arg;
        NodeToken *t = current_cntx->findFunction(current());
        if (t == NULL)
        {
            Error.error = 1;
            Error.error_message = string_format("function %s not found %s", current()->text.c_str(), linepos().c_str());
            return;
        }
        next();
        next();
        if (t->_nodetype == defExtFunctionNode)
        {
            NodeExtCallFunction function = NodeExtCallFunction(t);
            current_node = current_node->addChild(function);
            sav_nb_arg = function._link->getChildAtPos(1)->children.size();
        }
        else
        {
            NodeCallFunction function = NodeCallFunction(t);
            current_node = current_node->addChild(function);
            sav_nb_arg = function._link->getChildAtPos(1)->children.size();
        }
        parseArguments();
        if (Error.error)
        {
            return;
        }

        if (sav_nb_arg != nb_argument)
        {
            Error.error = 1;

            Error.error_message = string_format("Expected %d arguments got %d %s\n", sav_nb_arg, nb_argument, linepos().c_str());
            return;
        }
        Error.error = 0;
        current_node = current_node->parent;

        return;
    }

    void parseComparaison(string target)
    {
        // resParse res;
        Error.error = 0;
        NodeComparator cn = NodeComparator();
        current_node = current_node->addChild(cn);

        // res._nd=NodeToken();
        parseExpr();
        if (Error.error)
        {
            return;
        }
        // token *t=current();
        current_node->_token = current();
        next();
        parseExpr();
        if (Error.error)
        {
            return;
        }
        next();

        current_node->target = target;
        // cn.target=target;
        // cn.addChild(left._nd);
        // cn.addChild(right._nd);

        Error.error = 0;
        current_node = current_node->parent;
        return;
    }

    void parseStatement()
    {
        Error.error = 0;
        // resParse result;
        // NodeStatement statement;
        // current_node=current_node->addChild(statement);

        // on demarre avec la function
        if (Match(TokenKeyword) && MatchKeyword(KeyWordReturn))
        {
            next();
            if (Match(TokenSemicolon))
            {
                current_node->addChild(NodeReturn());
                next();
                return;
            }
            else
            {
                Error.error = 1;
                Error.error_message = string_format("d Expected ; %s", linepos().c_str());
                return;
            }
        }
        else if (Match(TokenIdentifier) && Match(TokenOpenParenthesis, 1))
        {
            parseFunctionCall();
            if (Error.error)
            {
                return;
            }
            else
            {
                if (Match(TokenSemicolon))
                {
                    Error.error = 0;
                    // current_node->addChild(res._nd);
                    // current_node=current_node->parent;
                    // result._nd = res._nd;
                    next();
                    return;
                }
                else
                {
                    Error.error = 1;
                    Error.error_message = string_format("Expected ; %s", linepos().c_str());
                    next();
                    return;
                }
            }
        }
        if (Match(TokenIdentifier) && Match(TokenPlusPlus, 1))
        {
            NodeAssignement d = NodeAssignement();
            current_node = current_node->addChild(d);
            getVariable(true);
            if (Error.error)
            {
                return;
            }
            NodeUnitary g = NodeUnitary();
            current_node = current_node->addChild(g);
            prev();
            getVariable(false);
            if (Error.error)
            {
                return;
            }
            current_node->addChild(NodeOperator(current()));
            next();
            current_node = current_node->parent;
            current_node = current_node->parent;
            if (!Match(TokenSemicolon) && !Match(TokenCloseParenthesis))
            {
                Error.error = 1;
                Error.error_message = string_format("Expected ; %s", linepos().c_str());
                next();
                return;
            }
            Error.error = 0;
            next();
            return;
        }
        else if (Match(TokenIdentifier))
        {
            NodeAssignement nd;
            current_node = current_node->addChild(nd);
            getVariable(true);
            if (Error.error)
            {
                return;
            }
            if (Match(TokenEqual))
            {
                next();
                parseExpr();
                if (Error.error)
                {
                    return;
                }

                if (!Match(TokenSemicolon)) //&& !Match(TokenCloseParenthesis))
                {
                    Error.error = 1;
                    Error.error_message = string_format("Expected ici ; %s", linepos().c_str());
                    // next();
                    return;
                }
                // current_node->addChild(left._nd);
                // current_node->addChild(right._nd);
                Error.error = 0;
                // result._nd = nd;
                // current_node=current_node->parent;
                current_node = current_node->parent;
                next();
                return;
            }
            else
            {
                Error.error = 1;
                Error.error_message = string_format("Expected = %s", linepos().c_str());
                return;
            }
        }

        else if (MatchKeyword(KeywordElse) && Match(TokenKeyword))
        {
            // on tente le for(){}
            token *fort = current();
            Context cntx;
            cntx.name = current()->text;
            // //printf("entering f %d %s %s %x\n", current_cntx->_global->children.size(), current_cntx->_global->name.c_str(), current()->text.c_str(), (uint64_t)current_cntx->_global);
            Context *k = (*(current_cntx)).addChild(cntx);
            current_cntx = k;
            // string target =string_format("label_%d%s",for_if_num,k->name.c_str());
            targetList.push(string_format("label_%d%s", for_if_num, current_cntx->name.c_str()));
            //=target;
            for_if_num++;

            NodeElse ndf = NodeElse(fort);
            ndf.target = targetList.pop();
            current_node = current_node->addChild(ndf);
            next();

            parseBlockStatement();
            if (Error.error)
            {
                return;
            }

            // current_node->target=target;

            // resParse result;

            Error.error = 0;
            // result._nd = ndf;
            // next();
            current_cntx = current_cntx->parent;
            current_node = current_node->parent;
            //  current_node=current_node->parent;
            return;
        }
        else if (MatchKeyword(KeywordWhile) && Match(TokenKeyword))
        {
            // on tente le for(){}
            token *fort = current();
            Context cntx;
            cntx.name = current()->text;
            // //printf("entering f %d %s %s %x\n", current_cntx->_global->children.size(), current_cntx->_global->name.c_str(), current()->text.c_str(), (uint64_t)current_cntx->_global);
            Context *k = (*(current_cntx)).addChild(cntx);
            current_cntx = k;
            string target = string_format("label_%d%s", for_if_num, k->name.c_str());
            //=target;
            for_if_num++;
            next();
            if (Match(TokenOpenParenthesis))
            {
                NodeWhile ndf = NodeWhile(fort);
                ndf.target = target;
                current_node = current_node->addChild(ndf);
                next();

                // printf(" *************** on parse comp/n");
                parseComparaison(target);
                if (Error.error)
                {
                    return;
                }
                ////printf("on a parse %s\n",comparator._nd._token->text.c_str());
                // printf(" *************** on parse inc/n");

                parseBlockStatement();
                if (Error.error)
                {
                    return;
                }

                // current_node->target=target;

                // resParse result;

                Error.error = 0;
                // result._nd = ndf;
                // next();
                current_cntx = current_cntx->parent;
                current_node = current_node->parent;
                //  current_node=current_node->parent;
                return;
            }
            else
            {
                // resParse res;
                Error.error = 1;
                Error.error_message = string_format("expecting ( %s", linepos().c_str());
                next();
                return;
            }
        }
        else if (MatchKeyword(KeywordIf) && Match(TokenKeyword))
        {
            // on tente le for(){}
            // token *fort=current();
            Context cntx;
            cntx.name = current()->text;
            // //printf("entering f %d %s %s %x\n", current_cntx->_global->children.size(), current_cntx->_global->name.c_str(), current()->text.c_str(), (uint64_t)current_cntx->_global);
            Context *k = (*(current_cntx)).addChild(cntx);
            current_cntx = k;
            // string target =string_format("label_%d%s",for_if_num,k->name.c_str());
            targetList.push(string_format("label_%d%s", for_if_num, current_cntx->name.c_str()));
            //=target;
            for_if_num++;
            // next();
            if (Match(TokenOpenParenthesis, 1))
            {
                NodeIf ndf = NodeIf(current());
                ndf.target = targetList.get();
                next();
                current_node = current_node->addChild(ndf);
                next();

                // printf(" *************** on parse comp/n");
                parseComparaison(targetList.pop());
                if (Error.error)
                {
                    return;
                }
                ////printf("on a parse %s\n",comparator._nd._token->text.c_str());
                // printf(" *************** on parse inc/n");

                parseBlockStatement();
                if (Error.error)
                {
                    return;
                }

                // current_node->target=target;

                // resParse result;

                Error.error = 0;
                // result._nd = ndf;
                // next();
                current_cntx = current_cntx->parent;
                current_node = current_node->parent;
                //  current_node=current_node->parent;
                return;
            }
            else
            {
                // resParse res;
                Error.error = 1;
                Error.error_message = string_format("expecting ( %s", linepos().c_str());
                next();
                return;
            }
        }
        else if (MatchKeyword(KeywordFor) && Match(TokenKeyword))
        {
            // on tente le for(){}
            // token *fort=current();
            Context cntx;
            cntx.name = current()->text;
            // //printf("entering f %d %s %s %x\n", current_cntx->_global->children.size(), current_cntx->_global->name.c_str(), current()->text.c_str(), (uint64_t)current_cntx->_global);
            current_cntx = (*(current_cntx)).addChild(cntx);
            // current_cntx = k;
            // string target =string_format("label_%d%s",for_if_num,current_cntx->name.c_str());
            targetList.push(string_format("label_%d%s", for_if_num, current_cntx->name.c_str()));
            //=target;
            for_if_num++;
            // next();
            if (Match(TokenOpenParenthesis, 1))
            {
                NodeFor ndf = NodeFor(current());
                ndf.target = targetList.get();
                next();
                current_node = current_node->addChild(ndf);
                next();
                current_node = current_node->addChild(NodeStatement());
                parseStatement();
                if (Error.error)
                {
                    return;
                }
                current_node = current_node->parent;
                // printf(" *************** on parse comp/n");
                parseComparaison(targetList.pop());
                if (Error.error)
                {
                    return;
                }
                ////printf("on a parse %s\n",comparator._nd._token->text.c_str());
                // printf(" *************** on parse inc/n");
                parseStatement();
                if (Error.error)
                {
                    return;
                }

                parseBlockStatement();
                if (Error.error)
                {
                    return;
                }

                // current_node->target=target;

                // resParse result;

                Error.error = 0;
                // result._nd = ndf;
                // next();
                current_cntx = current_cntx->parent;
                current_node = current_node->parent;
                //  current_node=current_node->parent;
                return;
            }
            else
            {
                // resParse res;
                Error.error = 1;
                Error.error_message = string_format("expecting ( %s", linepos().c_str());
                next();
                return;
            }
        }

        else if (Match(TokenKeyword) && MatchKeyword(KeywordVarType))
        {
            // printf("trying to create %s\n", current()->text.c_str());
            parseType();
            if (Error.error)
            {
                Error.error = 1;

                return;
            }

            parseVariableForCreation();
            if (Error.error)
            {

                return;
            }
            NodeToken nd = nodeTokenList.pop();
            NodeToken f = nodeTokenList.pop();
            auto var = createNodeLocalVariableForCreation(&nd, &f);
            // printf("111&&&&&&&dddddddddd&&&&qssdqsdqsd& %s\n", nodeTypeNames[var._nodetype].c_str());
            string var_name = nd._token->text;
            // pritnf()
            current_cntx->addVariable(var);

            if (Match(TokenSemicolon))
            {
                Error.error = 0;
                // result._nd = var;
                current_node->addChild(var);
                // current_node = current_node->parent;
                next();
                return;
            }

            if (Match(TokenEqual))
            {
                //  NodeStatement ndsmt;
                current_node->addChild(var);
                NodeAssignement nd;
                current_node = current_node->addChild(nd);
                next();
                auto left = createNodeLocalVariableForStore(var);
                // copyPrty(type._nd, &var);
                current_node->addChild(left);
                parseExpr();

                if (Error.error)
                {

                    return;
                }

                if (!Match(TokenSemicolon))
                {
                    Error.error = 1;
                    Error.error_message = string_format("Expected ; %s", linepos().c_str());
                    next();
                    return;
                }
                // nd.addChild(left);
                // nd.addChild(right._nd);
                // ndsmt.addChild(nd);
                Error.error = 0;
                // result._nd = ndsmt;
                // current_node->addChild(ndsmt);
                current_node = current_node->parent;
                next();
                return;
            }
            else
            {
                Error.error = 1;
                Error.error_message = string_format(" expecting ;  ou = %s", linepos().c_str());
                return;
            }

            return;
        }
        return;
    }

    void parseBlockStatement()
    {
        // resParse result;

        NodeBlockStatement nbStmnt;
        Context cntx;
        cntx.name = string_format("%d", block_statement_num);
        block_statement_num++;
        current_cntx = current_cntx->addChild(cntx);
        current_node = current_node->addChild(nbStmnt);
        next();
        while (!Match(TokenCloseCurlyBracket) && !Match(TokenEndOfFile))
        {
            // printf("on tente aouter un stamt\n");
            parseStatement();
            if (Error.error)
            {
                return;
            }
        }
        if (Match(TokenEndOfFile))
        {
            Error.error = 1;
            Error.error_message = string_format("expected } %s", linepos().c_str());
            next();
            return;
        }
        Error.error = 0;
        // result._nd = nbStmnt;
        current_cntx = current_cntx->parent;
        current_node = current_node->parent;
        next();
        return;
    }

    void parseDefFunction(NodeToken oritype)
    {
        Error.error = 0;
        bool ext_function = false;
        // printf("entering function\n");
        if (isExternal)
        {
            ext_function = true;
            isExternal = false;
        }
        // resParse result;
        token *func = current();

        if (current_cntx->findFunction(current()) != NULL)
        {

            Error.error = 1;
            Error.error_message = string_format("function already declared in the scope for %s", linepos().c_str());
            next();
            return;
        }
        if (ext_function)
        {
            NodeDefExtFunction function = NodeDefExtFunction(func);
            function.addChild(oritype);
            //  function.addChild(arguments._nd);

            current_node = current_node->addChild(function);
            current_cntx->parent->addFunction(current_node);
        }
        else
        {
            NodeDefFunction function = NodeDefFunction(func);
            function.addChild(oritype);
            //  function.addChild(arguments._nd);

            current_node = current_node->addChild(function);
            current_cntx->parent->addFunction(current_node);
        }
        // on ajoute un nouveau contexte
        Context cntx;
        cntx.name = current()->text;
        Context *k = current_cntx->addChild(cntx);
        current_cntx = k;
        stack_size = 16;
        block_statement_num = 0;
        next();
        next();
        parseCreateArguments();
        if (Error.error)
        {
            return;
        }
        if (!Match(TokenCloseParenthesis))
        {
            Error.error = 1;
            Error.error_message = string_format("Expected ) %s", linepos().c_str());
            next();
            return;
        }
        next();
        if (ext_function)
        {
            if (Match(TokenSemicolon))
            {
                //   NodeDefExtFunction function = NodeDefExtFunction(func);
                //  function.addChild(oritype);
                //  function.addChild(arguments._nd);
                // current_cntx->parent->addFunction(function);
                // current_node->addChild(function);
                // result._nd = function;
                Error.error = 0;
                current_cntx = current_cntx->parent;
                current_node = current_node->parent;
                next();
                return;
            }
            else
            {
                Error.error = 1;
                Error.error_message = string_format("Impossible to redifine external function expected ; %s", linepos().c_str());
                next();
                return;
            }
        }
        else
        {
            if (Match(TokenOpenCurlyBracket))
            {
                // NodeDefFunction function = NodeDefFunction(func);
                // function.addChild(oritype);
                // function.addChild(arguments._nd);
                // current_cntx->parent->addFunction(function);
                // current_node = current_node->addChild(function);

                parseBlockStatement();
                if (Error.error)
                {
                    return;
                }
                // current_node->addChild(blocsmt._nd);
                // current_node = current_node->parent;
                current_node->stack_pos = stack_size;
                // result._nd = function;
                Error.error = 0;
                current_cntx = current_cntx->parent;
                current_node = current_node->parent;
                return;
            }
            else
            {
                Error.error = 1;
                Error.error_message = string_format("Expected { %s", linepos().c_str());
                next();
                return;
            }
        }

        return;
    }

    void parseType()
    {

        // resParse res;
        NodeToken _nd;
        if (Match(TokenExternal))
        {
            isExternal = true;
            next();
        }
        if (Match(TokenKeyword) && MatchKeyword(KeywordVarType))
        {
            _nd._nodetype = typeNode;
            _nd._token = current();

            next();
            if (Match(TokenStar))
            {
                _nd.isPointer = true;
                next();
            }
            else
            {
                _nd.isPointer = false;
            }
        }
        else
        {
            Error.error = 1;
            Error.error_message = string_format("expecting __ext__ or variable type %s", linepos().c_str());
            next();
            return;
        }
        Error.error = 0;
        nodeTokenList.push(_nd);
        return;
    }

    void parseVariableForCreation()
    {
        current_cntx->findVariable(current(), true);
        if (search_result != NULL)
        {
            // resParse res;
            Error.error = 1;
            Error.error_message = string_format("variable already declared in the scope for %s", linepos().c_str());
            next();
            return;
        }
        if (Match(TokenOpenBracket, 1))
        {
            // we are in the case led[];
            
            NodeToken var = NodeToken(current());
            next();
            next();
            if (Match(TokenNumber))
            {
                token *num = current();
                if (num->_vartype->_varType == __unit16_t__)
                {
                    next();
                    if (Match(TokenCloseBracket))
                    {
                        var.isPointer = true;
                        var._nodetype = defGlobalVariableNode; // we can't have arrays in the stack
                        var._total_size = stringToInt(num->text);
                        next();
                        // resParse result;
                        Error.error = 0;
                        nodeTokenList.push(var);
                        return;
                    }
                    else
                    {
                        // resParse res;
                        Error.error = 1;
                        Error.error_message = string_format("expecting ] %s", linepos().c_str());
                        next();
                        return;
                    }
                }
                else
                {
                    // resParse res;
                    Error.error = 1;
                    Error.error_message = string_format("expecting an integer %s", linepos().c_str());
                    next();
                    return;
                }
            }
        }
        else
        {
            NodeToken nd = NodeToken(current());
            // resParse result;
            // result._nd = nd;
            Error.error = 0;
            nodeTokenList.push(nd);
            next();
            return;
        }
    }

    void parseProgram()
    {

        // NodeProgram program;
        // Context cntx = Context();
        current_cntx->name = "main";
        current_node = &program;
        // current_cntx = &cntx;

        // resParse result;
        Error.error = 0;
        while (Match(TokenEndOfFile) == false)
        {
            parseType();
            if (Error.error)
            {

                return;
            }

            if (Match(TokenIdentifier))
            {
                if (Match(TokenOpenParenthesis, 1))
                {
                    parseDefFunction(nodeTokenList.get());
                    if (Error.error)
                    {
                        return;
                    }
                    // program.addChild(res._nd);
                }
                else
                {

                    parseVariableForCreation();
                    if (Error.error)
                    {

                        return;
                    }
                    NodeToken nd = nodeTokenList.pop();
                    if (isExternal)
                    {

                        NodeDefExtGlobalVariable var = NodeDefExtGlobalVariable(nd);
                        NodeToken t = nodeTokenList.pop();
                        copyPrty(&t, &var);
                        program.addChild(var);
                        current_cntx->addVariable(var);
                        isExternal = false;
                    }
                    else
                    {
                        NodeDefGlobalVariable var = NodeDefGlobalVariable(nd);
                        NodeToken t = nodeTokenList.pop();
                        copyPrty(&t, &var);
                        program.addChild(var);
                        current_cntx->addVariable(var);
                    }
                    if (Match(TokenSemicolon))
                    {

                        next();
                    }
                    else
                    {
                        Error.error = 1;
                        Error.error_message = string_format(" expecting ;  ou = %s", linepos().c_str());
                        return;
                    }
                }
            }
            else
            {
                Error.error = 1;
                Error.error_message = string_format("expected identifier %s", linepos().c_str());
                next();
                return;
            }
        }
        // result._nd = program;
        Error.error = 0;
        // printf("exit programm\n");
        return;
    }

private:
    Tokens _tks;
};
#ifdef __CONSOLE_ESP32
executable executecmd;
// string strcompile;
bool exeExist;
Parser p = Parser();

void parse_c(Console *cons, vector<string> args)
{
    exeExist = false;
    freeBinary(&executecmd);
   // bool debug = false;
   //__parser_debug=true;
    if (args.size() > 0)
    {
        __parser_debug = true;
    }

    p.clean();
    p.clean2();

    // _push(config.ENDLINE);
    // Serial.printf(termColor.Cyan);

    string rt = "";
    for (string s : cons->script)

    {
        rt = rt + s + "\n";
    }
    rt = rt + '\0';
//cons->script.clear();
    Script sc(rt);
    rt.clear();
    _tks.init();
    tokenizer(&sc);
    cons->pushToConsole("***********TOKENISATION DONE***********");

    p.parse();
    if (Error.error)
    {

        while (p.Match(TokenEndOfFile) == false)
        {
            p.next();
        }
        p.clean();
        p.clean2();
        cons->pushToConsole(Error.error_message.c_str());
    }
    else
    {
        // prettyPrint(program, "");
        cons->pushToConsole("***********PARSING DONE*********");

        program.visitNode(&program);

        cons->pushToConsole("***********COMPILING DONE*********");
        // p.cleanint();
        p.clean();

        cons->pushToConsole("***********AFTER CLEAN*********");
        // printf("%d\n",_content.size());
        int s = _header.size();
        for (int i = 0; i < s; i++)
        {

            _content.push_front(_header.back());
            _header.pop_back();
        }
        cons->pushToConsole("***********CREATE EXECUTABLE*********");
        executecmd = createExectutable(&_content, __parser_debug);
        // strcompile = "";
        p.clean2();
        // Serial.printf(config.ESC_RESET);

        if (executecmd.error.error == 0)
        {
            exeExist = true;
            vector<string> d;
            // d.push_back("main");
            cons->pushToConsole("***********START RUN*********");
            executeBinary("main", executecmd);
            // run2(d);
        }
        else
        {
            exeExist = false;
            Serial.printf(termColor.Red);
            cons->pushToConsole(executecmd.error.error_message.c_str());
            Serial.printf(config.ESC_RESET);
        }
    }
    __parser_debug=false;
}
void parsec_cEsc(Console *cons)
{
    cons->displayf = false;
    vector<string> f;
    if(cons->cmode==edit)
    {
        cons->storeCurrentLine();
    }
    parse_c(cons, f);
}
class __INIT_PARSER
{
public:
    __INIT_PARSER()
    {
        LedOS.addKeywordCommand("compile", parse_c);
        LedOS.addEscCommand(18, parsec_cEsc);
    }
};
__INIT_PARSER _init_parser;
#endif
