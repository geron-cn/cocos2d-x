// automatically generated by the FlatBuffers compiler, do not modify

#ifndef FLATBUFFERS_GENERATED_CSTABCONTROL_FLATBUFFERS_H_
#define FLATBUFFERS_GENERATED_CSTABCONTROL_FLATBUFFERS_H_

#include "flatbuffers/flatbuffers.h"


namespace flatbuffers {

struct WidgetOptions;
struct PanelOptions;
struct Color;
struct TabControlOption;
struct TabHeaderOption;
struct TabItemOption;
struct ResourceItemData;


struct TabControlOption : private flatbuffers::Table {
    const WidgetOptions *nodeOptions() const { return GetPointer<const WidgetOptions *>(4); }
    int32_t headerPlace() const { return GetField<int32_t>(6, 0); }
    int32_t headerWidth() const { return GetField<int32_t>(8, 0); }
    int32_t headerHeight() const { return GetField<int32_t>(10, 0); }
    float selectedTabZoom() const { return GetField<float>(12, 0); }
    int32_t selectedTabIndex() const { return GetField<int32_t>(14, 0); }
    const flatbuffers::Vector<flatbuffers::Offset<TabItemOption>> *tabItems() const { return GetPointer<const flatbuffers::Vector<flatbuffers::Offset<TabItemOption>> *>(16); }
    bool Verify(flatbuffers::Verifier &verifier) const {
        return VerifyTableStart(verifier) &&
            VerifyField<flatbuffers::uoffset_t>(verifier, 4 /* nodeOptions */) &&
            verifier.VerifyTable(nodeOptions()) &&
            VerifyField<int32_t>(verifier, 6 /* headerPlace */) &&
            VerifyField<int32_t>(verifier, 8 /* headerWidth */) &&
            VerifyField<int32_t>(verifier, 10 /* headerHeight */) &&
            VerifyField<float>(verifier, 12 /* selectedTabZoom */) &&
            VerifyField<int32_t>(verifier, 14 /* selectedTabIndex */) &&
            VerifyField<flatbuffers::uoffset_t>(verifier, 16 /* tabItems */) &&
            verifier.Verify(tabItems()) &&
            verifier.VerifyVectorOfTables(tabItems()) &&
            verifier.EndTable();
    }
};

struct TabControlOptionBuilder {
    flatbuffers::FlatBufferBuilder &fbb_;
    flatbuffers::uoffset_t start_;
    void add_nodeOptions(flatbuffers::Offset<WidgetOptions> nodeOptions) { fbb_.AddOffset(4, nodeOptions); }
    void add_headerPlace(int32_t headerPlace) { fbb_.AddElement<int32_t>(6, headerPlace, 0); }
    void add_headerWidth(int32_t headerWidth) { fbb_.AddElement<int32_t>(8, headerWidth, 0); }
    void add_headerHeight(int32_t headerHeight) { fbb_.AddElement<int32_t>(10, headerHeight, 0); }
    void add_selectedTabZoom(float selectedTabZoom) { fbb_.AddElement<float>(12, selectedTabZoom, 0); }
    void add_selectedTabIndex(int32_t selectedTabIndex) { fbb_.AddElement<int32_t>(14, selectedTabIndex, 0); }
    void add_tabItems(flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<TabItemOption>>> tabItems) { fbb_.AddOffset(16, tabItems); }
    TabControlOptionBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
    TabControlOptionBuilder &operator=(const TabControlOptionBuilder &);
    flatbuffers::Offset<TabControlOption> Finish() {
        auto o = flatbuffers::Offset<TabControlOption>(fbb_.EndTable(start_, 7));
        return o;
    }
};

inline flatbuffers::Offset<TabControlOption> CreateTabControlOption(flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<WidgetOptions> nodeOptions = 0,
    int32_t headerPlace = 0,
    int32_t headerWidth = 0,
    int32_t headerHeight = 0,
    float selectedTabZoom = 0,
    int32_t selectedTabIndex = 0,
    flatbuffers::Offset<flatbuffers::Vector<flatbuffers::Offset<TabItemOption>>> tabItems = 0) {
    TabControlOptionBuilder builder_(_fbb);
    builder_.add_tabItems(tabItems);
    builder_.add_selectedTabIndex(selectedTabIndex);
    builder_.add_selectedTabZoom(selectedTabZoom);
    builder_.add_headerHeight(headerHeight);
    builder_.add_headerWidth(headerWidth);
    builder_.add_headerPlace(headerPlace);
    builder_.add_nodeOptions(nodeOptions);
    return builder_.Finish();
}


struct TabHeaderOption : private flatbuffers::Table {
    const WidgetOptions *nodeOptions() const { return GetPointer<const WidgetOptions *>(4); }
    const ResourceData *fontRes() const { return GetPointer<const ResourceData *>(6); }
    int32_t fontSize() const { return GetField<int32_t>(8, 0); }
    const flatbuffers::String *titleText() const { return GetPointer<const flatbuffers::String *>(10); }
    const Color *textColor() const { return GetStruct<const Color *>(12); }
    const ResourceData *normalBackFile() const { return GetPointer<const ResourceData *>(14); }
    const ResourceData *pressBackFile() const { return GetPointer<const ResourceData *>(16); }
    const ResourceData *disableBackFile() const { return GetPointer<const ResourceData *>(18); }
    const ResourceData *crossNormalFile() const { return GetPointer<const ResourceData *>(20); }
    const ResourceData *crossDisableFile() const { return GetPointer<const ResourceData *>(22); }
    bool Verify(flatbuffers::Verifier &verifier) const {
        return VerifyTableStart(verifier) &&
            VerifyField<flatbuffers::uoffset_t>(verifier, 4 /* nodeOptions */) &&
            verifier.VerifyTable(nodeOptions()) &&
            VerifyField<flatbuffers::uoffset_t>(verifier, 6 /* fontRes */) &&
            verifier.VerifyTable(fontRes()) &&
            VerifyField<int32_t>(verifier, 8 /* fontSize */) &&
            VerifyField<flatbuffers::uoffset_t>(verifier, 10 /* titleText */) &&
            verifier.Verify(titleText()) &&
            VerifyField<Color>(verifier, 12 /* textColor */) &&
            VerifyField<flatbuffers::uoffset_t>(verifier, 14 /* normalBackFile */) &&
            verifier.VerifyTable(normalBackFile()) &&
            VerifyField<flatbuffers::uoffset_t>(verifier, 16 /* pressBackFile */) &&
            verifier.VerifyTable(pressBackFile()) &&
            VerifyField<flatbuffers::uoffset_t>(verifier, 18 /* disableBackFile */) &&
            verifier.VerifyTable(disableBackFile()) &&
            VerifyField<flatbuffers::uoffset_t>(verifier, 20 /* crossNormalFile */) &&
            verifier.VerifyTable(crossNormalFile()) &&
            VerifyField<flatbuffers::uoffset_t>(verifier, 22 /* crossDisableFile */) &&
            verifier.VerifyTable(crossDisableFile()) &&
            verifier.EndTable();
    }
};

struct TabHeaderOptionBuilder {
    flatbuffers::FlatBufferBuilder &fbb_;
    flatbuffers::uoffset_t start_;
    void add_nodeOptions(flatbuffers::Offset<WidgetOptions> nodeOptions) { fbb_.AddOffset(4, nodeOptions); }
    void add_fontRes(flatbuffers::Offset<ResourceData> fontRes) { fbb_.AddOffset(6, fontRes); }
    void add_fontSize(int32_t fontSize) { fbb_.AddElement<int32_t>(8, fontSize, 0); }
    void add_titleText(flatbuffers::Offset<flatbuffers::String> titleText) { fbb_.AddOffset(10, titleText); }
    void add_textColor(const Color *textColor) { fbb_.AddStruct(12, textColor); }
    void add_normalBackFile(flatbuffers::Offset<ResourceData> normalBackFile) { fbb_.AddOffset(14, normalBackFile); }
    void add_pressBackFile(flatbuffers::Offset<ResourceData> pressBackFile) { fbb_.AddOffset(16, pressBackFile); }
    void add_disableBackFile(flatbuffers::Offset<ResourceData> disableBackFile) { fbb_.AddOffset(18, disableBackFile); }
    void add_crossNormalFile(flatbuffers::Offset<ResourceData> crossNormalFile) { fbb_.AddOffset(20, crossNormalFile); }
    void add_crossDisableFile(flatbuffers::Offset<ResourceData> crossDisableFile) { fbb_.AddOffset(22, crossDisableFile); }
    TabHeaderOptionBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
    TabHeaderOptionBuilder &operator=(const TabHeaderOptionBuilder &);
    flatbuffers::Offset<TabHeaderOption> Finish() {
        auto o = flatbuffers::Offset<TabHeaderOption>(fbb_.EndTable(start_, 10));
        return o;
    }
};

inline flatbuffers::Offset<TabHeaderOption> CreateTabHeaderOption(flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<WidgetOptions> nodeOptions = 0,
    flatbuffers::Offset<ResourceData> fontRes = 0,
    int32_t fontSize = 0,
    flatbuffers::Offset<flatbuffers::String> titleText = 0,
    const Color *textColor = 0,
    flatbuffers::Offset<ResourceData> normalBackFile = 0,
    flatbuffers::Offset<ResourceData> pressBackFile = 0,
    flatbuffers::Offset<ResourceData> disableBackFile = 0,
    flatbuffers::Offset<ResourceData> crossNormalFile = 0,
    flatbuffers::Offset<ResourceData> crossDisableFile = 0) {
    TabHeaderOptionBuilder builder_(_fbb);
    builder_.add_crossDisableFile(crossDisableFile);
    builder_.add_crossNormalFile(crossNormalFile);
    builder_.add_disableBackFile(disableBackFile);
    builder_.add_pressBackFile(pressBackFile);
    builder_.add_normalBackFile(normalBackFile);
    builder_.add_textColor(textColor);
    builder_.add_titleText(titleText);
    builder_.add_fontSize(fontSize);
    builder_.add_fontRes(fontRes);
    builder_.add_nodeOptions(nodeOptions);
    return builder_.Finish();
}

struct TabItemOption : private flatbuffers::Table {
    const TabHeaderOption *header() const { return GetPointer<const TabHeaderOption *>(4); }
    const PanelOptions *container() const { return GetPointer<const PanelOptions *>(6); }
    bool Verify(flatbuffers::Verifier &verifier) const {
        return VerifyTableStart(verifier) &&
            VerifyField<flatbuffers::uoffset_t>(verifier, 4 /* header */) &&
            verifier.VerifyTable(header()) &&
            VerifyField<flatbuffers::uoffset_t>(verifier, 6 /* container */) &&
            verifier.VerifyTable(container()) &&
            verifier.EndTable();
    }
};

struct TabItemOptionBuilder {
    flatbuffers::FlatBufferBuilder &fbb_;
    flatbuffers::uoffset_t start_;
    void add_header(flatbuffers::Offset<TabHeaderOption> header) { fbb_.AddOffset(4, header); }
    void add_container(flatbuffers::Offset<PanelOptions> container) { fbb_.AddOffset(6, container); }
    TabItemOptionBuilder(flatbuffers::FlatBufferBuilder &_fbb) : fbb_(_fbb) { start_ = fbb_.StartTable(); }
    TabItemOptionBuilder &operator=(const TabItemOptionBuilder &);
    flatbuffers::Offset<TabItemOption> Finish() {
        auto o = flatbuffers::Offset<TabItemOption>(fbb_.EndTable(start_, 2));
        return o;
    }
};

inline flatbuffers::Offset<TabItemOption> CreateTabItemOption(flatbuffers::FlatBufferBuilder &_fbb,
    flatbuffers::Offset<TabHeaderOption> header = 0,
    flatbuffers::Offset<PanelOptions> container = 0) {
    TabItemOptionBuilder builder_(_fbb);
    builder_.add_container(container);
    builder_.add_header(header);
    return builder_.Finish();
}


inline const TabControlOption *GetTabControlOption(const void *buf) { return flatbuffers::GetRoot<TabControlOption>(buf); }

inline bool VerifyTabControlOptionBuffer(flatbuffers::Verifier &verifier) { return verifier.VerifyBuffer<TabControlOption>(); }

inline void FinishTabControlOptionBuffer(flatbuffers::FlatBufferBuilder &fbb, flatbuffers::Offset<TabControlOption> root) { fbb.Finish(root); }

}  // namespace flatbuffers

#endif  // FLATBUFFERS_GENERATED_CSTABCONTROL_FLATBUFFERS_H_
