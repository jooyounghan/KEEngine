# 확장 가능한 ReflectionSystem 사용 가이드

## 개요

이전의 ReflectionSystem은 새로운 프로퍼티 타입을 추가할 때마다 `isReflectXXX()` 같은 메서드를 IReflectProperty에 추가하고, 모든 구현 클래스를 수정해야 했습니다. 

새로운 시스템에서는:
1. **EReflectPropertyType** 열거형에 새로운 타입만 추가
2. 새로운 프로퍼티 클래스 구현
3. 기존 코드는 수정할 필요 없음

## 새로운 아키텍처의 핵심 요소

### 1. 타입 열거형 (EReflectPropertyType)

```cpp
DECLARE_ENUM_CLASS(EReflectPropertyType, uint8,
    POD,      // Plain Old Data (int, float, etc.)
    Object,   // ReflectObject 타입
    Vector,   // std::vector 타입
    Enum      // 열거형 타입
);
```

### 2. 타입 안전 캐스팅

```cpp
// 새로운 방법: 템플릿 기반 안전한 캐스팅
IReflectProperty* property = ...;

// POD 프로퍼티로 캐스팅
if (auto* podProp = property->as<IReflectPODProperty>())
{
    // POD 프로퍼티 사용
}

// Vector 프로퍼티로 캐스팅
if (auto* vectorProp = property->as<IReflectVectorProperty>())
{
    size_t size = vectorProp->getSize(object);
    vectorProp->resize(object, newSize);
}

// Enum 프로퍼티로 캐스팅
if (auto* enumProp = property->as<IReflectEnumProperty>())
{
    int64 value = enumProp->getEnumValue(object);
    const char* name = enumProp->getEnumName(value);
}
```

### 3. 타입 기반 분기

```cpp
// 새로운 방법: switch 문으로 깔끔하게 처리
switch (property->getPropertyType())
{
case EReflectPropertyType::POD:
    // POD 처리
    break;
case EReflectPropertyType::Object:
    // Object 처리
    break;
case EReflectPropertyType::Vector:
    // Vector 처리
    break;
case EReflectPropertyType::Enum:
    // Enum 처리
    break;
}
```

## 사용 예제

### 예제 1: Vector 프로퍼티 사용

```cpp
class MyObject : public IReflectObject
{
private:
    std::vector<int> _numbers;

public:
    std::vector<int>& getNumbers() { return _numbers; }
    const std::vector<int>& getNumbers() const { return _numbers; }
    void setNumbers(const std::vector<int>& numbers) { _numbers = numbers; }
};

// 메타데이터 등록
void MyObject::registerMetaData()
{
    ReflectMetaData* metaData = getMetaData();
    
    // Vector 프로퍼티 등록
    auto* vectorProp = new ReflectVectorProperty<MyObject, int>(
        "_numbers",
        &MyObject::getNumbers,
        static_cast<ConstGetter<MyObject, std::vector<int>>>(&MyObject::getNumbers),
        &MyObject::setNumbers
    );
    metaData->addProperty(vectorProp);
}

// 사용
MyObject obj;
IReflectProperty* prop = obj.getMetaData()->getPropertyByName("_numbers");

if (auto* vectorProp = prop->as<IReflectVectorProperty>())
{
    size_t size = vectorProp->getSize(&obj);
    vectorProp->resize(&obj, 10);
    vectorProp->clear(&obj);
}
```

### 예제 2: Enum 프로퍼티 사용

```cpp
enum class EColor
{
    Red = 0,
    Green = 1,
    Blue = 2
};

class MyObject : public IReflectObject
{
private:
    EColor _color;

public:
    EColor& getColor() { return _color; }
    const EColor& getColor() const { return _color; }
    void setColor(const EColor& color) { _color = color; }
};

// 메타데이터 등록
void MyObject::registerMetaData()
{
    ReflectMetaData* metaData = getMetaData();
    
    // Enum 프로퍼티 등록
    auto* enumProp = new ReflectEnumProperty<MyObject, EColor>(
        "_color",
        &MyObject::getColor,
        static_cast<ConstGetter<MyObject, EColor>>(&MyObject::getColor),
        &MyObject::setColor
    );
    
    // Enum 값 등록
    enumProp->registerEnumValue("Red", static_cast<int64>(EColor::Red));
    enumProp->registerEnumValue("Green", static_cast<int64>(EColor::Green));
    enumProp->registerEnumValue("Blue", static_cast<int64>(EColor::Blue));
    
    metaData->addProperty(enumProp);
}

// 사용
MyObject obj;
IReflectProperty* prop = obj.getMetaData()->getPropertyByName("_color");

if (auto* enumProp = prop->as<IReflectEnumProperty>())
{
    // 현재 값 가져오기
    int64 value = enumProp->getEnumValue(&obj);
    const char* name = enumProp->getEnumName(value);
    
    // 값 설정하기
    enumProp->setEnumValue(&obj, static_cast<int64>(EColor::Green));
    
    // 모든 가능한 값 가져오기
    const std::vector<int64>& values = enumProp->getAllEnumValues();
    const std::vector<const char*>& names = enumProp->getAllEnumNames();
}
```

### 예제 3: 범용 프로퍼티 처리

```cpp
void processProperty(IReflectObject* object, IReflectProperty* property)
{
    switch (property->getPropertyType())
    {
    case EReflectPropertyType::POD:
        {
            if (auto* podProp = property->as<IReflectPODProperty>())
            {
                // POD 프로퍼티 처리
                StaticBuffer<256> buffer;
                property->getToString(object, &buffer);
                // buffer 사용...
            }
        }
        break;
        
    case EReflectPropertyType::Vector:
        {
            if (auto* vectorProp = property->as<IReflectVectorProperty>())
            {
                size_t size = vectorProp->getSize(object);
                // Vector 요소들 처리...
            }
        }
        break;
        
    case EReflectPropertyType::Enum:
        {
            if (auto* enumProp = property->as<IReflectEnumProperty>())
            {
                int64 value = enumProp->getEnumValue(object);
                const char* name = enumProp->getEnumName(value);
                // Enum 값 처리...
            }
        }
        break;
        
    case EReflectPropertyType::Object:
        {
            IReflectObject* childObject = property->getReflectObject(object);
            // 재귀적으로 처리...
        }
        break;
    }
}
```

## 새로운 프로퍼티 타입 추가하기

새로운 프로퍼티 타입을 추가하려면:

1. **EReflectPropertyType에 새로운 열거값 추가**
```cpp
DECLARE_ENUM_CLASS(EReflectPropertyType, uint8,
    POD,
    Object,
    Vector,
    Enum,
    Map        // 새로운 타입!
);
```

2. **인터페이스 클래스 생성** (예: IReflectMapProperty.h)
```cpp
class IReflectMapProperty
{
public:
    virtual ~IReflectMapProperty() = default;
    
    virtual size_t getSize(const IReflectObject* object) const = 0;
    // 기타 Map 관련 메서드들...
};
```

3. **구현 클래스 생성** (예: ReflectMapProperty.h)
```cpp
template<typename ObjectType, typename KeyType, typename ValueType>
class ReflectMapProperty 
    : public IReflectMapProperty
    , public ReflectPropertyBase<ObjectType, std::map<KeyType, ValueType>>
{
public:
    inline virtual EReflectPropertyType getPropertyType() const override 
    { 
        return EReflectPropertyType::Map; 
    }
    
    // IReflectMapProperty 메서드 구현...
};
```

4. **IReflectProperty.hpp에 템플릿 특수화 추가**
```cpp
template<>
inline IReflectMapProperty* IReflectProperty::as<IReflectMapProperty>()
{
    if (getPropertyType() == EReflectPropertyType::Map)
    {
        return static_cast<IReflectMapProperty*>(this);
    }
    return nullptr;
}
```

이렇게 하면 기존 코드는 전혀 수정하지 않고도 새로운 프로퍼티 타입을 추가할 수 있습니다!

## 이전 코드와의 호환성

기존 코드와의 호환성을 위해 legacy 메서드들은 유지되고 있습니다:
- `isReflectObject()`, `isPODProperty()` - 여전히 작동
- `getReflectObject()`, `getPODProperty()` - 여전히 작동

하지만 새로운 코드에서는 `getPropertyType()`과 `as<T>()`를 사용하는 것을 권장합니다.

## 장점 요약

1. **확장성**: 새로운 타입 추가 시 기존 코드 수정 불필요
2. **타입 안전성**: 템플릿 기반 `as<T>()`로 안전한 캐스팅
3. **가독성**: switch 문으로 명확한 타입 분기
4. **유지보수성**: 한 곳(열거형)에서 모든 타입 관리
