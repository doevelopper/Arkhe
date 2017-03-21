#ifndef ARKHE_CORE_JSONPARSEERROR_HPP
#define ARKHE_CORE_JSONPARSEERROR_HPP


namespace Json 
{
    class JsonParseError
    {
    public:
        enum ParseError 
        {
            NoError = 0,
            UnterminatedObject,
            MissingNameSeparator,
            UnterminatedArray,
            MissingValueSeparator,
            IllegalValue,
            TerminationByNumber,
            IllegalNumber,
            IllegalEscapeSequence,
            IllegalUTF8String,
            UnterminatedString,
            MissingObject,
            DeepNesting,
            DocumentTooLarge,
            GarbageAtEnd
        };

        int        offset;
        ParseError error;
    
        JsonParseError();
        virtual ~JsonParseError();
    };
}
#endif

