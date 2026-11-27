#ifndef VERSUS_STATS_DATA_H
#define VERSUS_STATS_DATA_H

enum EStatsType {
    STATSTYPE_Render = 0, STATSTYPE_Game = 1, STATSTYPE_Hardware = 2, STATSTYPE_Net = 6
};
enum EStatsDataType { STATSDATATYPE_Integer, STATSDATATYPE_Float, STATSDATATYPE_String };
enum EStatsUnit {
    STATSUNIT_Default, STATSUNIT_Combined_Default_MSec, STATSUNIT_Combined_Default_Default,
    STATSUNIT_Byte, STATSUNIT_KByte, STATSUNIT_MByte, STATSUNIT_MSec
};
struct FStatsData { INT Index; EStatsDataType DataType; EStatsUnit Unit; };

class FStats {
public:
    DWORD Unknown00;
    UBOOL Registered[8];
    template<class T> struct Values {
        TArray<T> Current, Previous;
        TArray<FString> Descriptions, FullDescriptions;
    };
    Values<DWORD> Integers;
    Values<FLOAT> Floats;
    Values<FString> Strings;
    TArray<FStatsData> Stats[8];
    struct FMovingAverage {
        INT WriteIndex, Window, Count;
        DWORD Unknown0c;
        TArray<DWORD> Samples;
    };
    TArray<FMovingAverage> History;
    void Clear();
    void SmoothCounter(INT Index, INT Window);
    INT RegisterStats(EStatsType Type, EStatsDataType DataType, FString Description,
                      FString SectionDescription, EStatsUnit Unit);
};
extern FStats GStats;

#endif
