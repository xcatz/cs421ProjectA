#include "parser.h"
#include <string>
#include <stack>
using namespace std;

InvalidTokenException::InvalidTokenException(string expected, string actual)
{
    ExpectedValue = expected;
    ActualValue = actual;
}

TokenObject::TokenObject()
{
    Word = "";
    Token = UNKOWN;
}

TokenObject::TokenObject(string word, WordType type)
{
    Word = word;
    Token = type;
}

Parser::Parser()
{
    stack<TokenObject> dummy;

    contents = dummy;
    //ctor
}

Parser::~Parser()
{
    //dtor
}

void Parser::AddToken(TokenObject Content)
{
    contents.push(Content);
}

void Parser::AddToken(string word, WordType type)
{
    TokenObject dummy(word, type);
    AddToken(dummy);
}

bool Parser::Process()
{
    return false;
}

bool Parser::VerbTensePeriod()
{
    TokenObject nextToken = contents.top();
    TokenObject prevToken;
    if(nextToken.Token == PERIOD)
    {
        ;
        prevToken = nextToken;
        contents.pop();
        nextToken = contents.top();
        //<tense> := VERBPAST  | VERBPASTNEG | VERB | VERBNEG
        switch(nextToken.Token)
        {
            case VERBPAST:
            case VERBPASTNEG:
            case VERB:
            case VERBNEG:
                prevToken = nextToken;
                contents.pop();
                nextToken = contents.top();
                //<verb> ::= WORD2
                if(nextToken.Token == WORD2)
                {
                    contents.pop();
                    return true;
                }
            default:
                return false;
        }

    }


    return false;
}

bool Parser::NounBePeriod()
{

    TokenObject nextToken = contents.top();
    TokenObject prevToken;
    if(nextToken.Token == PERIOD)
    {
        prevToken = nextToken;
        contents.pop();
        nextToken = contents.top();
        switch(nextToken.Token)
        {
            case IS:
            case WAS:
                prevToken = nextToken;
                contents.pop();
                nextToken = contents.top();
                switch(nextToken.Token)
                {
                    case WORD1:
                    case WORD2:
                    case PRONOUN:
                        contents.pop();
                        return true;
                    default:
                        return false;
                }
            default:
                    return false;
        }
    }


    return false;
}

bool Parser::NounObject()
{

    TokenObject nextToken = contents.top();
    TokenObject prevToken;
    switch (nextToken.Token)
    {
        case OBJECT:
            prevToken = nextToken;
            contents.pop();
            nextToken = contents.top();
            switch(nextToken.Token)
            {
                case WORD1:
                case WORD2:
                case PRONOUN:
                    contents.pop();
                    return true;
                default:
                    return false;
            }
        default:
            return false;
    }
    return false;
}

bool Parser::NounDestination()
{
    ;
    return false;
}

bool Parser::ConnectorNounSubject()
{

    TokenObject nextToken = contents.top();
    TokenObject prevToken;
    switch (nextToken.Token)
    {
        case DESTINATION:
            prevToken = nextToken;
            contents.pop();
            nextToken = contents.top();
            switch(nextToken.Token)
            {
                case WORD1:
                case WORD2:
                case PRONOUN:
                    contents.pop();
                    return true;
                default:
                    return false;
            }
        default:
            return false;
    }
    return false;
}


