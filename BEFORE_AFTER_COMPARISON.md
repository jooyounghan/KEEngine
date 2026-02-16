# Before & After: ReflectionSystem 리팩토링

## 문제 상황 (Before)

### 새 프로퍼티 타입 추가 시 필요한 작업

예를 들어 `ReflectVector`를 추가하려면:

#### 1. IReflectProperty.h 수정
```cpp
class IReflectProperty
{
public:
    virtual bool isReflectVector() const = 0;  // ← 추가!
    virtual IReflectVector* getReflectVector() = 0;  // ← 추가!
};
```

#### 2. ReflectPODProperty.h 수정
```cpp
class ReflectPODProperty
{
public:
    virtual bool isReflectVector() const { return false; }  // ← 구현!
    virtual IReflectVector* getReflectVector() { return nullptr; }  // ← 구현!
};
```

#### 3. ReflectObjectProperty.h 수정
```cpp
class ReflectObjectProperty
{
public:
    virtual bool isReflectVector() const { return false; }  // ← 구현!
    virtual IReflectVector* getReflectVector() { return nullptr; }  // ← 구현!
};
```

#### 4. 그리고 ReflectEnum을 추가한다면?
모든 과정을 다시 반복... 😰

**문제점:**
- 🔴 새 타입마다 모든 클래스 수정 필요
- 🔴 N개의 프로퍼티 타입 × M개의 구현 클래스 = N×M 번의 수정
- 🔴 실수하기 쉬움
- 🔴 유지보수 어려움

---

## 해결 방안 (After)

### 새 프로퍼티 타입 추가 시 필요한 작업

예를 들어 `ReflectMap`을 추가하려면:

#### 1. EReflectPropertyType 열거형에 추가
```cpp
DECLARE_ENUM_CLASS(EReflectPropertyType, uint8,
    POD,
    Object,
    Vector,
    Enum,
    Map        // ← 여기만 추가!
);
```

#### 2. 새 인터페이스 생성
```cpp
// IReflectMapProperty.h
class IReflectMapProperty
{
public:
    virtual size_t getSize(const IReflectObject* object) const = 0;
    // Map 관련 메서드들...
};
```

#### 3. 새 구현 클래스 생성
```cpp
// ReflectMapProperty.h
template<typename ObjectType, typename KeyType, typename ValueType>
class ReflectMapProperty 
    : public IReflectMapProperty
    , public ReflectPropertyBase<ObjectType, std::map<KeyType, ValueType>>
{
public:
    virtual EReflectPropertyType getPropertyType() const override 
    { 
        return EReflectPropertyType::Map; 
    }
    
    // IReflectMapProperty 구현...
};
```

#### 4. as<T>() 템플릿 특수화 추가
```cpp
// IReflectProperty.hpp에 추가
template<>
inline IReflectMapProperty* IReflectProperty::as<IReflectMapProperty>()
{
    return getPropertyType() == EReflectPropertyType::Map 
        ? static_cast<IReflectMapProperty*>(this) 
        : nullptr;
}
```

**끝!** 기존 클래스들(ReflectPODProperty, ReflectObjectProperty 등)은 수정 불필요! ✨

**장점:**
- ✅ 기존 코드 수정 불필요
- ✅ 한 곳(열거형)에서 타입 관리
- ✅ 타입 안전성 보장
- ✅ 확장성 극대화

---

## 사용 방법 비교

### Before: if-else 체인
```cpp
void processProperty(IReflectProperty* property)
{
    if (property->isReflectObject())
    {
        // Object 처리
    }
    else if (property->isPODProperty())
    {
        // POD 처리
    }
    else if (property->isReflectVector())  // 추가...
    {
        // Vector 처리
    }
    else if (property->isReflectEnum())    // 추가...
    {
        // Enum 처리
    }
    // 계속 추가...
}
```

### After: switch-case
```cpp
void processProperty(IReflectProperty* property)
{
    switch (property->getPropertyType())
    {
    case EReflectPropertyType::Object:
        // Object 처리
        break;
    case EReflectPropertyType::POD:
        // POD 처리
        break;
    case EReflectPropertyType::Vector:
        // Vector 처리
        break;
    case EReflectPropertyType::Enum:
        // Enum 처리
        break;
    }
}
```

---

## 타입 캐스팅 비교

### Before: 수동 확인 및 캐스팅
```cpp
if (property->isPODProperty())
{
    IReflectPODProperty* podProp = property->getPODProperty();
    // 사용...
}

// Vector는? Enum은? 
// 각각 isPODProperty(), isReflectVector(), isReflectEnum() 필요
```

### After: 템플릿 기반 안전한 캐스팅
```cpp
if (auto* podProp = property->as<IReflectPODProperty>())
{
    // 사용...
}

if (auto* vectorProp = property->as<IReflectVectorProperty>())
{
    // 사용...
}

if (auto* enumProp = property->as<IReflectEnumProperty>())
{
    // 사용...
}

// 모든 타입에 동일한 패턴 사용!
```

---

## 실제 예제: ReflectSerializer 비교

### Before
```cpp
for (const IReflectProperty* property : properties)
{
    if (property->isReflectObject())
    {
        reflectObjectProperties.push_back(property);
    }
    else if (property->isPODProperty())
    {
        // POD 처리...
    }
    // Vector는? 또 else if 추가...
}
```

### After
```cpp
for (const IReflectProperty* property : properties)
{
    switch (property->getPropertyType())
    {
    case EReflectPropertyType::Object:
        reflectObjectProperties.push_back(property);
        break;
    case EReflectPropertyType::POD:
    case EReflectPropertyType::Vector:  // ← 쉽게 추가!
    case EReflectPropertyType::Enum:    // ← 쉽게 추가!
        {
            // 모든 직렬화 가능 타입 처리...
        }
        break;
    }
}
```

---

## 확장성 비교

### Before: O(N×M) 복잡도
- N개의 새 타입 추가 시
- M개의 기존 클래스 모두 수정 필요
- **수정 포인트: N × M**

### After: O(N) 복잡도
- N개의 새 타입 추가 시
- 기존 클래스 수정 불필요
- **수정 포인트: N**

---

## 결론

| 항목 | Before | After |
|------|--------|-------|
| 새 타입 추가 시 수정 | 모든 클래스 | 새 클래스만 |
| 코드 중복 | 많음 | 없음 |
| 타입 안전성 | 약함 | 강함 |
| 가독성 | if-else 체인 | switch-case |
| 확장성 | 낮음 | 높음 |
| 유지보수성 | 어려움 | 쉬움 |

**새로운 구조로 인해 향후 ReflectMap, ReflectSet, ReflectUnion 등 어떤 타입이든 쉽게 추가할 수 있습니다!** 🎉
