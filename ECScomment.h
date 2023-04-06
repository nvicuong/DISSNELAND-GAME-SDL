#pragma once

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset> //using bitset instead of bool array or vector to optimize memory and performance
#include <array>

class Component; //lớp cơ bản của một thành phần trong game, có chứa ba hàm ảo để được kế thừa bởi các lớp thành phần khác.
class Entity; //lớp chứa các thành phần của một đối tượng trong game. Mỗi đối tượng có một "active" flag để xác định xem đối tượng đó đang hoạt động hay không.
class Manager; //quản lý các đối tượng và các nhóm của chúng. Nó cũng cung cấp các hàm để cập nhật và vẽ các đối tượng, cũng như thêm, xóa và truy xuất các đối tượng từ các nhóm.

using ComponentID = std::size_t; //using size_t to optimize datatype
using Group = std::size_t;


inline ComponentID getNewComponentTypeID() //using inline function to optimize performance with a basic function
{
	static ComponentID lastID = 0u; //using static variable 
	return lastID++;
}

template <typename T> inline ComponentID getComponentTypeID() noexcept // using noexcept can optimize the code to not catch any exceptions that may occur during execution, helping to speed up execution and improve program reliability. Using the noexcept keyword does not guarantee that a function cannot throw exceptions, only that if it does throw an exception, the program will immediately terminate
{
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32; //using constexpr to optimize code by computing values at compile-time instead of run-time
constexpr std::size_t maxGroups = 32;


using ComponentBitset = std::bitset<maxComponents>;
using GroupBitset = std::bitset<maxGroups>;


using ComponentArray = std::array<Component*, maxComponents>;

class Component
{
public:
	Entity* entity;

	virtual void init() {} //using virtual function in base class in order that subclasses can override this function
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}


};

class Entity
{
private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components; //là một vector các unique_ptr chứa các con trỏ tới các thành phần.

	ComponentArray componentArray; //là một mảng các con trỏ tới các thành phần, được sử dụng để truy xuất thành phần theo kiểu động.
	ComponentBitset componentBitSet; //là một bitset để xác định các thành phần có trong thực thể hay không.
	GroupBitset groupBitset; //là một bitset để xác định thực thể thuộc nhóm nào.

	/*Trong class Entity, components và componentArray đều dùng để lưu trữ các thành phần của một đối tượng Entity.Tuy nhiên, chúng có mục đích sử dụng khác nhau.
		components là một vector các unique_ptr trỏ tới các thành phần(Component) của một Entity.unique_ptr được sử dụng để quản lý bộ nhớ động của các thành phần này.Việc sử dụng vector giúp cho việc quản lý các thành phần trở nên dễ dàng hơn, cũng như tăng tính linh hoạt của class Entity trong việc thêm hoặc xóa các thành phần.
		componentArray là một mảng các con trỏ tới các thành phần(Component) của một Entity.Nó được sử dụng để giúp Entity có thể truy cập các thành phần của nó dễ dàng hơn.Khi cần truy cập thành phần, Entity sử dụng một số duy nhất(được sinh ra bởi getComponentTypeID) để truy cập phần tử tương ứng trong mảng componentArray, do đó giúp cho việc truy cập thành phần trở nên nhanh chóng và hiệu quả hơn.*/
public:
	Entity(Manager& mManager) : manager(mManager) {}
	void update()
	{
		for (auto& c : components) c->update();

	}
	void draw() { for (auto& c : components) c->draw(); }
	bool isActive() const { return active; }
	void destroy() { active = false; }

	bool hasGroup(Group mGroup)
	{
		return groupBitset[mGroup];
	}

	void addGroup(Group mGroup);
	void delGroup(Group mGroup)
	{
		groupBitset[mGroup] = false;
	}
	/*Hàm delGroup() là một phương thức của lớp Entity.Nó được sử dụng để xóa một nhóm(Group) đã được gán cho đối tượng Entity thông qua addGroup().
		Cách hoạt động của hàm là thiết lập bit tương ứng với mGroup trong groupBitset thành false, đánh dấu rằng đối tượng Entity không thuộc nhóm đó nữa.Điều này có nghĩa là đối tượng Entity sẽ không được xử lý trong bất kỳ hệ thống nào liên quan đến mGroup nữa.*/

	template <typename T> bool hasComponent() const //xác định xem một đối tượng có chứa một loại thành phần được chỉ định hay không.
	{
		return componentBitSet[getComponentTypeID<T>()];
	}

	template <typename T, typename... TArgs> //thêm một thành phần mới vào một đối tượng.
	T& addComponent(TArgs&&... mArgs)
	{
		T* c(new T(std::forward<TArgs>(mArgs)...));
		c->entity = this;
		std::unique_ptr<T> uPtr{ c };
		components.emplace_back(std::move(uPtr));

		componentArray[getComponentTypeID<T>()] = c;
		componentBitSet[getComponentTypeID<T>()] = true;

		c->init();
		return *c;
	}
	/*Trong template này, TArgs&&... mArgs là một pack của các tham số truyền vào hàm addComponent, trong đó TArgs là một pack bất kỳ các kiểu dữ liệu.TArgs&& định nghĩa các tham số này là rvalue reference, cho phép truyền các đối tượng đang được xây dựng hoặc các đối tượng tạm thời đến hàm addComponent.

		std::forward<TArgs>(mArgs)... được sử dụng để chuyển tiếp các tham số truyền vào của addComponent đến hàm khởi tạo của đối tượng T.Khi đó, std::forward sẽ giữ nguyên giá trị lvalue hoặc rvalue của tham số được truyền vào, dựa vào kiểu tham số của TArgs.

		Nếu TArgs là một lvalue reference, std::forward sẽ giữ nguyên giá trị lvalue của tham số được truyền vào, trong khi nếu TArgs là một rvalue reference, std::forward sẽ giữ nguyên giá trị rvalue của tham số được truyền vào.

		Việc sử dụng std::forward giúp hàm addComponent truyền các đối tượng đến hàm khởi tạo của đối tượng T với cùng kiểu tham số, bất kể đối tượng đó là lvalue hay rvalue, và cho phép đối tượng được chuyển tiếp một cách hiệu quả và an toàn.*/

	template<typename T> T& getComponent() const //lấy tham chiếu tới Component của Entity dựa theo ComponentTypeID; khi này hàm chính là biến giá trị ptr, hàm chính là một biến, thay đổi giá trị hàm tương đương thay đổi giá trị biến trả về trong hàm
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}

};

class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities; //là một vector chứa tất cả các unique_ptr của các Entity được tạo ra trong game.
	std::array<std::vector<Entity*>, maxGroups> groupedEntities; //là một mảng các vector, với kích thước maxGroups, mỗi phần tử của mảng chứa các con trỏ đến các Entity được phân loại vào từng nhóm tương ứng.

public:
	void update()
	{
		for (auto& e : entities) e->update();
	}
	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	void refresh() //erase all Entity that are not active also not belong to any group in groupedEntities
	{
		for (auto i(0u); i < maxGroups; i++)
		{
			auto& v(groupedEntities[i]);
			v.erase(
				std::remove_if(std::begin(v), std::end(v), //belong to <algorithm> ; "std::remove_if(ForwardIterator first, ForwardIterator last, UnaryPredicate pred)", "UnaryPredicate pred" is the bool function to check, if it's true, function erases all the elements that satisfy that bool function and return the poiter to the first element of satisfied sequence
					[i](Entity* mEntity) //using lambda function to check
					{
						return !mEntity->isActive() || !mEntity->hasGroup(i); //if mEntity is no active or no in any group then return true to erase this entity
					}
				),
				std::end(v));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities),
			[](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive(); //if any element in entities has no actived no longer then return true
			}),
			std::end(entities));
	}

	void AddToGroup(Entity* mEntity, Group mGroup) //trả về một vector chứa tất cả các Entity được phân loại vào một nhóm được chỉ định.
	{
		groupedEntities[mGroup].emplace_back(mEntity);
	}

	std::vector<Entity*>& getGroup(Group mGroup) // tạo một Entity mới và thêm nó vào entities. Trả về một tham chiếu đến Entity mới tạo.
	{
		return groupedEntities[mGroup];
	}
	Entity& addEntity()
	{
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e }; //std::unique_ptr<Entity> create unique ptr that manages only this uPtr
		entities.emplace_back(std::move(uPtr)); //std::move(uPtr) is "moving" resources from one object to another instead of copying if using uPtr normally
		return *e;
	}
};
