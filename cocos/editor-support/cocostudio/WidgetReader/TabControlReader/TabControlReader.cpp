#include "tinyxml2/tinyxml2.h"
#include "flatbuffers/flatbuffers.h"
#include "cocostudio/WidgetReader/WidgetReader.h"
#include "cocostudio/CSParseBinary_generated.h"
#include "cocostudio/WidgetReader/TabControlReader/TabControlReader.h"
#include "cocostudio/WidgetReader/LayoutReader/LayoutReader.h"
#include "cocostudio/FlatBuffersSerialize.h"
#include "cocos/ui/UITabControl.h"


USING_NS_CC;
using namespace cocostudio;
using namespace flatbuffers;
using namespace cocos2d::ui;

IMPLEMENT_CLASS_NODE_READER_INFO(TabControlReader)

TabControlReader::TabControlReader()
{

}

TabControlReader* TabControlReader::_tabReaderInstance = nullptr;
TabControlReader* TabControlReader::getInstance()
{
    if (_tabReaderInstance == nullptr)
    {
        _tabReaderInstance = new  (std::nothrow) TabControlReader();
    }
    return _tabReaderInstance;
}

void TabControlReader::destroyInstance()
{
    CC_SAFE_DELETE(_tabReaderInstance);
}

flatbuffers::Offset<flatbuffers::Table> TabControlReader::createOptionsWithFlatBuffers(
    const tinyxml2::XMLElement* objectData, flatbuffers::FlatBufferBuilder* builder)
{
    auto temp = WidgetReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
    auto nodeOptions = *(Offset<WidgetOptions>*)(&temp);

    int headerPlace = 0;
    int headerWidth = 50;
    int headerHeight = 20;
    float selectedTabZoom = 0.0f;
    int selectedIndex = 0;
    std::vector<Offset<TabItemOption>>  tabItems;
    const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
    while (attribute)
    {
        std::string attriname = attribute->Name();
        std::string value = attribute->Value();

        if (attriname == "HeaderPlace")
        {
            headerPlace = atoi(value.c_str());
        }
        else if (attriname == "HeaderWidth")
        {
            headerWidth = atoi(value.c_str());
        }
        else if (attriname == "HeaderHeight")
        {
            headerHeight = atoi(value.c_str());
        }
        else if (attriname == "SelectedTabZoom")
        {
            selectedTabZoom = atof(value.c_str());
        }
        else if (attriname == "SelectedTabIndex")
        {
            selectedIndex = atoi(value.c_str());
        }
        attribute = attribute->Next();
    }

    bool containChildrenElement = false;
    const tinyxml2::XMLElement* child = objectData->FirstChildElement();
    while (child)
    {
        if (strcmp("Children", child->Name()) == 0)
        {
            containChildrenElement = true;
            break;
        }

        child = child->NextSiblingElement();
    }

    if (containChildrenElement)
    {
        child = child->FirstChildElement(); //first child
        bool hasItem = true;
        while (child && hasItem)
        {
            const tinyxml2::XMLAttribute* attribute = child->FirstAttribute();
            while (attribute)
            {
                std::string attriname = attribute->Name();
                std::string value = attribute->Value();

                if (attriname == "ctype" && value.compare("TabItemObjectData") == 0)
                {
                    auto itemOption = TabItemReader::getInstance()->createTabItemOptionWithFlatBuffers(child, builder);
                    tabItems.push_back(itemOption);
                    break;
                }
                else
                    hasItem = false;

                attribute = attribute->Next();
            }
            child = child->NextSiblingElement();
        }
    }

    auto options = CreateTabControlOption(*builder,
        nodeOptions,
        headerPlace,
        headerWidth,
        headerHeight,
        selectedTabZoom,
        selectedIndex,
        builder->CreateVector(tabItems));

    return *(Offset<Table>*)(&options);
}

void TabControlReader::setPropsWithFlatBuffers(cocos2d::Node* node, const flatbuffers::Table* nodeOption)
{
    auto tabControl = static_cast<cocos2d::ui::TabControl*>(node);
    auto options = (flatbuffers::TabControlOption*)nodeOption;

    int headerPlace = options->headerPlace();
    tabControl->setHeaderDockPlace((cocos2d::ui::TabControl::Dock)headerPlace);
    tabControl->setHeaderWidth(options->headerWidth());
    tabControl->setHeaderHeight(options->headerHeight());
    tabControl->setHeaderSelectedZoom(options->selectedTabZoom());
    tabControl->setSelectTab(options->selectedTabIndex());

    int tabItemCount = options->tabItems()->size();
    for (int i = 0; i < tabItemCount; i++)
    {
        auto item = options->tabItems()->Get(i);
        auto header = TabHeaderReader::getInstance()->createNodeWithFlatBuffers((Table*)item->header());
        auto container = LayoutReader::getInstance()->createNodeWithFlatBuffers((Table*)item->container());
        tabControl->insertTab(i, (TabHeader*)header, (Layout*)container);
    }
}

cocos2d::Node* TabControlReader::createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions)
{
    auto node = cocos2d::ui::TabControl::create();

    auto taboptions = (flatbuffers::TabControlOption*)nodeOptions;
    setPropsWithFlatBuffers(node, nodeOptions);

    auto nodereader = WidgetReader::getInstance();
    nodereader->setPropsWithFlatBuffers(node, (Table*)taboptions->nodeOptions());
    return node;
}

TabControlReader::~TabControlReader()
{

}


TabHeaderReader::TabHeaderReader()
{

}

TabHeaderReader::~TabHeaderReader()
{

}

TabHeaderReader* TabHeaderReader::_tabheaderReaderInstance = nullptr;
TabHeaderReader* TabHeaderReader::getInstance()
{
    if (_tabheaderReaderInstance == nullptr)
    {
        _tabheaderReaderInstance = new (std::nothrow) TabHeaderReader();
    }
    return _tabheaderReaderInstance;
}

void TabHeaderReader::destroyInstance()
{
    CC_SAFE_DELETE(_tabheaderReaderInstance);
}

flatbuffers::Offset<flatbuffers::Table> TabHeaderReader::createOptionsWithFlatBuffers(
    const tinyxml2::XMLElement* objectData, flatbuffers::FlatBufferBuilder* builder)
{
    auto temp = WidgetReader::getInstance()->createOptionsWithFlatBuffers(objectData, builder);
    auto nodeOptions = *(Offset<WidgetOptions>*)(&temp);

    
    int fontsize = 12;
    std::string text = "";
    cocos2d::Color4B textColor(255, 255, 255, 255);
    std::string fontName;

    int backgroundboxResourceType = 0;
    std::string backgroundboxPath = "";
    std::string backgroundboxPlistFile = "";

    int backGroundBoxSelectedResourceType = 0;
    std::string backGroundBoxSelectedPath = "";
    std::string backGroundBoxSelectedPlistFile = "";

    int frontCrossResourceType = 0;
    std::string frontCrossPath = "";
    std::string frontCrossPlistFile = "";

    int backGroundBoxDisabledResourceType = 0;
    std::string backGroundBoxDisabledPath = "";
    std::string backGroundBoxDisabledPlistFile = "";

    int frontCrossDisabledResourceType = 0;
    std::string frontCrossDisabledPath = "";
    std::string frontCrossDisabledPlistFile = "";


    std::string fontResourcePath = "";
    std::string fontResourcePlistFile = "";
    int fontResourceResourceType = 0;

    const tinyxml2::XMLAttribute* attribute = objectData->FirstAttribute();
    while (attribute)
    {
        std::string attriname = attribute->Name();
        std::string value = attribute->Value();

        if (attriname.compare("FontSize") == 0)
        {
            fontsize = atoi(value.c_str());
        }
        else if (attriname.compare("TitleText") == 0)
        {
            text = value;
        }
        attribute = attribute->Next();
    }


    const tinyxml2::XMLElement* child = objectData->FirstChildElement();
    while (child)
    {
        std::string name = child->Name();
        std::string value = child->Value();

        if (name == "TextColor")
        {
            attribute = child->FirstAttribute();
            while (attribute)
            {
                name = attribute->Name();
                std::string value = attribute->Value();

                if (name == "R")
                {
                    textColor.r = atoi(value.c_str());
                }
                else if (name == "G")
                {
                    textColor.g = atoi(value.c_str());
                }
                else if (name == "B")
                {
                    textColor.b = atoi(value.c_str());
                }

                attribute = attribute->Next();
            }
        } 
        else if (name == "NormalBackFileData")
        {
            std::string texture = "";
            std::string texturePng = "";

            attribute = child->FirstAttribute();

            while (attribute)
            {
                name = attribute->Name();
                std::string value = attribute->Value();

                if (name == "Path")
                {
                    backgroundboxPath = value;
                }
                else if (name == "Type")
                {
                    backgroundboxResourceType = getResourceType(value);
                }
                else if (name == "Plist")
                {
                    backgroundboxPlistFile = value;
                    texture = value;
                }

                attribute = attribute->Next();
            }

            if (backgroundboxResourceType == 1)
            {
                FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                fbs->_textures.push_back(builder->CreateString(texture));
            }
        }
        else if (name == "PressedBackFileData")
        {
            std::string texture = "";
            std::string texturePng = "";

            attribute = child->FirstAttribute();

            while (attribute)
            {
                name = attribute->Name();
                std::string value = attribute->Value();

                if (name == "Path")
                {
                    backGroundBoxSelectedPath = value;
                }
                else if (name == "Type")
                {
                    backGroundBoxSelectedResourceType = getResourceType(value);
                }
                else if (name == "Plist")
                {
                    backGroundBoxSelectedPlistFile = value;
                    texture = value;
                }

                attribute = attribute->Next();
            }

            if (backGroundBoxSelectedResourceType == 1)
            {
                FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                fbs->_textures.push_back(builder->CreateString(texture));
            }
        }
        else if (name == "NodeNormalFileData")
        {
            std::string texture = "";
            std::string texturePng = "";

            attribute = child->FirstAttribute();

            while (attribute)
            {
                name = attribute->Name();
                std::string value = attribute->Value();

                if (name == "Path")
                {
                    frontCrossPath = value;
                }
                else if (name == "Type")
                {
                    frontCrossResourceType = getResourceType(value);
                }
                else if (name == "Plist")
                {
                    frontCrossPlistFile = value;
                    texture = value;
                }

                attribute = attribute->Next();
            }

            if (frontCrossResourceType == 1)
            {
                FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                fbs->_textures.push_back(builder->CreateString(texture));
            }
        }
        else if (name == "DisableBackFileData")
        {
            std::string texture = "";
            std::string texturePng = "";

            attribute = child->FirstAttribute();

            while (attribute)
            {
                name = attribute->Name();
                std::string value = attribute->Value();

                if (name == "Path")
                {
                    backGroundBoxDisabledPath = value;
                }
                else if (name == "Type")
                {
                    backGroundBoxDisabledResourceType = getResourceType(value);
                }
                else if (name == "Plist")
                {
                    backGroundBoxDisabledPlistFile = value;
                    texture = value;
                }

                attribute = attribute->Next();
            }

            if (backGroundBoxDisabledResourceType == 1)
            {
                FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                fbs->_textures.push_back(builder->CreateString(texture));
            }
        }
        else if (name == "NodeDisableFileData")
        {
            std::string texture = "";
            std::string texturePng = "";

            attribute = child->FirstAttribute();

            while (attribute)
            {
                name = attribute->Name();
                std::string value = attribute->Value();

                if (name == "Path")
                {
                    frontCrossDisabledPath = value;
                }
                else if (name == "Type")
                {
                    frontCrossDisabledResourceType = getResourceType(value);
                }
                else if (name == "Plist")
                {
                    frontCrossDisabledPlistFile = value;
                    texture = value;
                }

                attribute = attribute->Next();
            }

            if (frontCrossDisabledResourceType == 1)
            {
                FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
                fbs->_textures.push_back(builder->CreateString(texture));
            }
        }
        else if (name == "FontResource")
        {
            attribute = child->FirstAttribute();

            while (attribute)
            {
                name = attribute->Name();
                std::string value = attribute->Value();

                if (name == "Path")
                {
                    fontResourcePath = value;
                }
                else if (name == "Type")
                {
                    fontResourceResourceType = getResourceType(value);
                }
                else if (name == "Plist")
                {
                    fontResourcePlistFile = value;
                }

                attribute = attribute->Next();
            }
        }

        child = child->NextSiblingElement();
    }
    Color f_textColor(255, textColor.r, textColor.g, textColor.b);
    auto option = CreateTabHeaderOption(*builder,
        nodeOptions,
        CreateResourceData(*builder,
        builder->CreateString(fontResourcePath),
        builder->CreateString(fontResourcePlistFile),
        fontResourceResourceType),
        fontsize,
        builder->CreateString(text),
        &f_textColor,
        CreateResourceData(*builder,
        builder->CreateString(backgroundboxPath),
        builder->CreateString(backgroundboxPlistFile),
        backgroundboxResourceType),
        CreateResourceData(*builder,
        builder->CreateString(backGroundBoxSelectedPath),
        builder->CreateString(backGroundBoxSelectedPlistFile),
        backGroundBoxSelectedResourceType),
        CreateResourceData(*builder,
        builder->CreateString(backGroundBoxDisabledPath),
        builder->CreateString(backGroundBoxDisabledPlistFile),
        backGroundBoxDisabledResourceType),
        CreateResourceData(*builder,
        builder->CreateString(frontCrossPath),
        builder->CreateString(frontCrossPlistFile),
        frontCrossResourceType),
        CreateResourceData(*builder,
        builder->CreateString(frontCrossDisabledPath),
        builder->CreateString(frontCrossDisabledPlistFile),
        frontCrossDisabledResourceType)
        );

    return  *(Offset<Table>*)(&option);
}

void TabHeaderReader::setPropsWithFlatBuffers(cocos2d::Node* node, const flatbuffers::Table* nodeOption)
{
    auto header = static_cast<cocos2d::ui::TabHeader*>(node);
    auto options = (flatbuffers::TabHeaderOption*)nodeOption;

    header->setTitleFontSize(options->fontSize());
    header->setTitleText(options->titleText()->c_str());
    auto textColor = options->textColor();
    Color3B titleColor(textColor->r(), textColor->g(), textColor->b());
    header->setTitleColor(titleColor);

    auto resourceData = options->fontRes();
    bool fileExist = false;
    std::string errorFilePath = "";
    std::string path = resourceData->path()->c_str();
    if (path != "")
    {
        if (FileUtils::getInstance()->isFileExist(path))
        {
            fileExist = true;
        }
        else
        {
            errorFilePath = path;
            fileExist = false;
        }
        if (fileExist)
        {
            header->setTitleFontName(path);
        }
    }

    bool backGroundFileExist = false;
    std::string backGroundErrorFilePath = "";
    auto backGroundDic = options->normalBackFile();
    int backGroundType = backGroundDic->resourceType();
    std::string backGroundTexturePath = backGroundDic->path()->c_str();
    switch (backGroundType)
    {
    case 0:
    {
        if (FileUtils::getInstance()->isFileExist(backGroundTexturePath))
        {
            backGroundFileExist = true;
        }
        else
        {
            backGroundErrorFilePath = backGroundTexturePath;
            backGroundFileExist = false;
        }
        break;
    }

    case 1:
    {
        std::string plist = backGroundDic->plistFile()->c_str();
        SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(backGroundTexturePath);
        if (spriteFrame)
        {
            backGroundFileExist = true;
        }
        else
        {
            if (FileUtils::getInstance()->isFileExist(plist))
            {
                ValueMap value = FileUtils::getInstance()->getValueMapFromFile(plist);
                ValueMap metadata = value["metadata"].asValueMap();
                std::string textureFileName = metadata["textureFileName"].asString();
                if (!FileUtils::getInstance()->isFileExist(textureFileName))
                {
                    backGroundErrorFilePath = textureFileName;
                }
            }
            else
            {
                backGroundErrorFilePath = plist;
            }
            backGroundFileExist = false;
        }
        break;
    }

    default:
        break;
    }
    if (backGroundFileExist)
    {
        header->loadTextureBackGround(backGroundTexturePath, (Widget::TextureResType)backGroundType);
    }

    //load background selected image
    bool backGroundSelectedfileExist = false;
    std::string backGroundSelectedErrorFilePath = "";
    auto backGroundSelectedDic = options->pressBackFile();
    int backGroundSelectedType = backGroundSelectedDic->resourceType();
    std::string backGroundSelectedTexturePath = backGroundSelectedDic->path()->c_str();
    switch (backGroundSelectedType)
    {
    case 0:
    {
        if (FileUtils::getInstance()->isFileExist(backGroundSelectedTexturePath))
        {
            backGroundSelectedfileExist = true;
        }
        else
        {
            backGroundSelectedErrorFilePath = backGroundSelectedTexturePath;
            backGroundSelectedfileExist = false;
        }
        break;
    }

    case 1:
    {
        std::string plist = backGroundSelectedDic->plistFile()->c_str();
        SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(backGroundSelectedTexturePath);
        if (spriteFrame)
        {
            backGroundSelectedfileExist = true;
        }
        else
        {
            if (FileUtils::getInstance()->isFileExist(plist))
            {
                ValueMap value = FileUtils::getInstance()->getValueMapFromFile(plist);
                ValueMap metadata = value["metadata"].asValueMap();
                std::string textureFileName = metadata["textureFileName"].asString();
                if (!FileUtils::getInstance()->isFileExist(textureFileName))
                {
                    backGroundSelectedErrorFilePath = textureFileName;
                }
            }
            else
            {
                backGroundSelectedErrorFilePath = plist;
            }
            backGroundSelectedfileExist = false;
        }
        break;
    }

    default:
        break;
    }
    if (backGroundSelectedfileExist)
    {
        header->loadTextureBackGroundSelected(backGroundSelectedTexturePath, (cocos2d::ui::Widget::TextureResType)backGroundSelectedType);
    }

    //load frontCross image
    bool frontCrossFileExist = false;
    std::string frontCrossErrorFilePath = "";
    auto frontCrossDic = options->crossNormalFile();
    int frontCrossType = frontCrossDic->resourceType();
    std::string frontCrossFileName = frontCrossDic->path()->c_str();
    switch (frontCrossType)
    {
    case 0:
    {
        if (FileUtils::getInstance()->isFileExist(frontCrossFileName))
        {
            frontCrossFileExist = true;
        }
        else
        {
            frontCrossErrorFilePath = frontCrossFileName;
            frontCrossFileExist = false;
        }
        break;
    }

    case 1:
    {
        std::string plist = frontCrossDic->plistFile()->c_str();
        SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frontCrossFileName);
        if (spriteFrame)
        {
            frontCrossFileExist = true;
        }
        else
        {
            if (FileUtils::getInstance()->isFileExist(plist))
            {
                ValueMap value = FileUtils::getInstance()->getValueMapFromFile(plist);
                ValueMap metadata = value["metadata"].asValueMap();
                std::string textureFileName = metadata["textureFileName"].asString();
                if (!FileUtils::getInstance()->isFileExist(textureFileName))
                {
                    frontCrossErrorFilePath = textureFileName;
                }
            }
            else
            {
                frontCrossErrorFilePath = plist;
            }
            frontCrossFileExist = false;
        }
        break;
    }

    default:
        break;
    }
    if (frontCrossFileExist)
    {
        header->loadTextureFrontCross(frontCrossFileName, (Widget::TextureResType)frontCrossType);
    }

    //load backGroundBoxDisabledData
    bool backGroundBoxDisabledFileExist = false;
    std::string backGroundBoxDisabledErrorFilePath = "";
    auto backGroundDisabledDic = options->disableBackFile();
    int backGroundDisabledType = backGroundDisabledDic->resourceType();
    std::string backGroundDisabledFileName = backGroundDisabledDic->path()->c_str();
    switch (backGroundDisabledType)
    {
    case 0:
    {
        if (FileUtils::getInstance()->isFileExist(backGroundDisabledFileName))
        {
            backGroundBoxDisabledFileExist = true;
        }
        else
        {
            backGroundBoxDisabledErrorFilePath = backGroundDisabledFileName;
            backGroundBoxDisabledFileExist = false;
        }
        break;
    }

    case 1:
    {
        std::string plist = backGroundDisabledDic->plistFile()->c_str();
        SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(backGroundDisabledFileName);
        if (spriteFrame)
        {
            backGroundBoxDisabledFileExist = true;
        }
        else
        {
            if (FileUtils::getInstance()->isFileExist(plist))
            {
                ValueMap value = FileUtils::getInstance()->getValueMapFromFile(plist);
                ValueMap metadata = value["metadata"].asValueMap();
                std::string textureFileName = metadata["textureFileName"].asString();
                if (!FileUtils::getInstance()->isFileExist(textureFileName))
                {
                    backGroundBoxDisabledErrorFilePath = textureFileName;
                }
            }
            else
            {
                backGroundBoxDisabledErrorFilePath = plist;
            }
            backGroundBoxDisabledFileExist = false;
        }
        break;
    }

    default:
        break;
    }
    if (backGroundBoxDisabledFileExist)
    {
        header->loadTextureBackGroundDisabled(backGroundDisabledFileName, (Widget::TextureResType)backGroundDisabledType);
    }

    ///load frontCrossDisabledData
    bool frontCrossDisabledFileExist = false;
    std::string frontCrossDisabledErrorFilePath = "";
    auto frontCrossDisabledDic = options->crossDisableFile();
    int frontCrossDisabledType = frontCrossDisabledDic->resourceType();
    std::string frontCrossDisabledFileName = frontCrossDisabledDic->path()->c_str();
    switch (frontCrossDisabledType)
    {
    case 0:
    {
        if (FileUtils::getInstance()->isFileExist(frontCrossDisabledFileName))
        {
            frontCrossDisabledFileExist = true;
        }
        else
        {
            frontCrossDisabledErrorFilePath = frontCrossDisabledFileName;
            frontCrossDisabledFileExist = false;
        }
        break;
    }

    case 1:
    {
        std::string plist = frontCrossDisabledDic->plistFile()->c_str();
        SpriteFrame* spriteFrame = SpriteFrameCache::getInstance()->getSpriteFrameByName(frontCrossDisabledFileName);
        if (spriteFrame)
        {
            frontCrossDisabledFileExist = true;
        }
        else
        {
            if (FileUtils::getInstance()->isFileExist(plist))
            {
                ValueMap value = FileUtils::getInstance()->getValueMapFromFile(plist);
                ValueMap metadata = value["metadata"].asValueMap();
                std::string textureFileName = metadata["textureFileName"].asString();
                if (!FileUtils::getInstance()->isFileExist(textureFileName))
                {
                    frontCrossDisabledErrorFilePath = textureFileName;
                }
            }
            else
            {
                frontCrossDisabledErrorFilePath = plist;
            }
            frontCrossDisabledFileExist = false;
        }
        break;
    }

    default:
        break;
    }
    if (frontCrossDisabledFileExist)
    {
        header->loadTextureFrontCrossDisabled(frontCrossDisabledFileName, (Widget::TextureResType)frontCrossDisabledType);
    }
}

cocos2d::Node* TabHeaderReader::createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions)
{
    auto node = cocos2d::ui::TabHeader::create();

    auto taboptions = (flatbuffers::TabHeaderOption*)nodeOptions;
    setPropsWithFlatBuffers(node, nodeOptions);

    auto nodereader = WidgetReader::getInstance();
    nodereader->setPropsWithFlatBuffers(node, (Table*)taboptions->nodeOptions());
    return node;
}

int TabHeaderReader::getResourceType(std::string key)
{
    if (key == "Normal" || key == "Default")
    {
        return 	0;
    }

    FlatBuffersSerialize* fbs = FlatBuffersSerialize::getInstance();
    if (fbs->_isSimulator)
    {
        if (key == "MarkedSubImage")
        {
            return 0;
        }
    }
    return 1;
}

TabItemReader::TabItemReader()
{

}

TabItemReader::~TabItemReader()
{

}
TabItemReader* TabItemReader::_tabItemReaderInstance = nullptr;
TabItemReader* TabItemReader::getInstance()
{
    if (_tabItemReaderInstance == nullptr)
    {
        _tabItemReaderInstance = new (std::nothrow) TabItemReader();
    }
    return _tabItemReaderInstance;
}

void TabItemReader::destroyInstance()
{
    CC_SAFE_DELETE(_tabItemReaderInstance);
}


flatbuffers::Offset<flatbuffers::TabItemOption> TabItemReader::createTabItemOptionWithFlatBuffers(
    const tinyxml2::XMLElement* objectData, flatbuffers::FlatBufferBuilder* builder)
{

    flatbuffers::Offset<TabHeaderOption> header;
    flatbuffers::Offset<PanelOptions> container;

    const tinyxml2::XMLElement* child = objectData->FirstChildElement();
    while (child)
    {
        std::string attriName = child->Name();
        if (attriName.compare("Header") == 0)
        {
            header = *(Offset<flatbuffers::TabHeaderOption>*)(&
                (TabHeaderReader::getInstance()->createOptionsWithFlatBuffers(child, builder)));
        }
        else if (attriName.compare("Container"))
        {
            container = *(Offset<flatbuffers::PanelOptions>*)(&
                (LayoutReader::getInstance()->createOptionsWithFlatBuffers(child, builder)));
        }

        child = child->NextSiblingElement();
    }
    auto options = CreateTabItemOption(*builder,
        *(Offset<flatbuffers::TabHeaderOption>*)(&header), 
        *(Offset<flatbuffers::PanelOptions>*)(&container)
        );
    return  *(&options);
}

void TabItemReader::setPropsWithFlatBuffers(cocos2d::Node* node, const flatbuffers::Table* nodeOption)
{
    // do nothing
}

cocos2d::Node* TabItemReader::createNodeWithFlatBuffers(const flatbuffers::Table* nodeOptions)
{
    // do nothing
    return nullptr;
}

flatbuffers::Offset<flatbuffers::Table> TabItemReader::createOptionsWithFlatBuffers(
    const tinyxml2::XMLElement* objectData, flatbuffers::FlatBufferBuilder* builder)
{
    
    // nothing
    return *(Offset<Table>*)(&CreateTabItemOption(*builder));
}
