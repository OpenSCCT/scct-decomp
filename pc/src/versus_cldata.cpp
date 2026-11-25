// versus_cldata.cpp -- ubi.com data printing, sizing and reference dispatch
#include "versus_cldata.h"
#include <stdio.h>
#include <string.h>

// clDataLong::ByteSize
unsigned clDataLong::ByteSize() const
{
    return sizeof(hostValue);
}

// clData::clData
clData::clData(Type dataType) : type(dataType)
{
}

// clDataLong::FormatAll
void clDataLong::FormatAll(clDataText &output, unsigned indent) const
{
    Format(output, indent);
}

// clDataStrRef::Print
void clDataStrRef::Print() const
{
    printf("\"%s\" ", text);
}

// clDataStrRef::ByteSize
unsigned clDataStrRef::ByteSize() const
{
    return strlen(text);
}

// clDataLong::Print
void clDataLong::Print() const
{
    printf(" L%d ", hostValue);
}

// clDataRef::Format
void clDataRef::Format(clDataText &output, unsigned indent) const
{
    target->Format(output, indent);
}

// clDataRef::FormatAll
void clDataRef::FormatAll(clDataText &output, unsigned indent) const
{
    target->FormatAll(output, indent);
}

// clDataRef::Print
void clDataRef::Print() const
{
    target->Print();
}

// clDataRef::AppendText
void clDataRef::AppendText(clDataText &output) const
{
    target->AppendText(output);
}

// clDataRef::ByteSize
unsigned clDataRef::ByteSize() const
{
    return target->ByteSize();
}

// clDataSerialize::clDataSerialize
clDataSerialize::clDataSerialize()
{
}
