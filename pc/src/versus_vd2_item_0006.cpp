// Work item 0006: Versus RVA 0x4990-0x4b6c.
// FString helpers from Unreal Engine 2 (Core/UnTemplate.h). FString is a
// TArray<TCHAR> holding Data, ArrayNum and ArrayMax.
//
// Not matched here (link-time-generated calling conventions):
//   0x4a10 FString::operator*(const TCHAR*) const  - this passed on the stack
//   0x4ab0 FString::operator*(const FString&) const - args in EAX/ESI
//   0x4af0 FString::FString(INT, const TCHAR*)       - args in EAX/ESI
typedef unsigned short TCHAR;
typedef int INT;

class FString {
public:
    FString(const TCHAR* In);               // RVA 0x46c0
    FString(const FString& Other);          // RVA 0x4640
    ~FString();                             // RVA 0x48b0
    FString& operator+=(const TCHAR* Str);  // RVA 0x4930
    FString operator+(const TCHAR* Str) const;

protected:
    TCHAR* Data;
    INT ArrayNum;
    INT ArrayMax;
};

// RVA 0x4990
FString FString::operator+(const TCHAR* Str) const
{
    return FString(*this) += Str;
}

// Output device base (Core/UnBuild.h / UnFile.h): interface only.
class FOutputDevice {
public:
    virtual void Serialize(const TCHAR* V, INT Event) = 0;
    virtual void Flush() {}
};

// String output device: FString is laid out after FOutputDevice's vtable
// pointer, so its constructor runs on this+4 before the vtable is stored.
class FStringOutputDevice : public FString, public FOutputDevice {
public:
    FStringOutputDevice(const TCHAR* InStr);
    void Serialize(const TCHAR* Data, INT Event);
};

// RVA 0x4b50
FStringOutputDevice::FStringOutputDevice(const TCHAR* InStr)
:   FString(InStr)
{
}
