// versus_cldata.h -- ubi.com data classes identified by the Versus type information
#ifndef VERSUS_CLDATA_H
#define VERSUS_CLDATA_H

namespace ExtAlloc {
    class OverrideAllocOperators {
    public:
        static void __stdcall operator delete(void *memory);

    protected:
        ~OverrideAllocOperators() {}
    };

    template<class T> class Allocator;
}

namespace _STL {
    template<class T> struct char_traits;
    template<class T, class Traits, class Alloc> class basic_string;
}

typedef _STL::basic_string<char, _STL::char_traits<char>, ExtAlloc::Allocator<char> > clDataText;

class clData : public virtual ExtAlloc::OverrideAllocOperators {
public:
    enum Type {
        String = 1,
        Binary = 2,
        Long = 4,
        StringReference = 5,
        Reference = 6
    };

    clData(Type dataType);
    virtual ~clData();
    virtual void Format(clDataText &output, unsigned indent) const = 0;
    virtual void FormatAll(clDataText &output, unsigned indent) const = 0;
    virtual void AppendText(clDataText &output) const = 0;
    virtual void Print() const = 0;
    virtual unsigned ByteSize() const = 0;

private:
    Type type;
};

class clDataRef : public clData {
public:
    virtual void Format(clDataText &output, unsigned indent) const;
    virtual void FormatAll(clDataText &output, unsigned indent) const;
    virtual void AppendText(clDataText &output) const;
    virtual void Print() const;
    virtual unsigned ByteSize() const;

private:
    clData *target;
};

class clDataLong : public clData {
public:
    virtual void Format(clDataText &output, unsigned indent) const;
    virtual void FormatAll(clDataText &output, unsigned indent) const;
    virtual void AppendText(clDataText &output) const;
    virtual void Print() const;
    virtual unsigned ByteSize() const;
    void SetNetworkValue(unsigned long value);

private:
    unsigned long networkValue;
    int hostValue;
};

class clDataStrRef : public clData {
public:
    virtual void Format(clDataText &output, unsigned indent) const;
    virtual void FormatAll(clDataText &output, unsigned indent) const;
    virtual void AppendText(clDataText &output) const;
    virtual void Print() const;
    virtual unsigned ByteSize() const;

private:
    const char *text;
};

class clDataSerialize : public virtual ExtAlloc::OverrideAllocOperators {
public:
    clDataSerialize();
    virtual ~clDataSerialize();
};

#endif
