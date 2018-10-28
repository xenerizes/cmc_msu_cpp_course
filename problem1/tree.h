#pragma once

#include <memory>

namespace bintree {
    template <typename T>
    struct TNode 
        // See comments below
        : std::enable_shared_from_this<TNode<T>> 
    {
        using TNodePtr = std::shared_ptr<TNode<T>>;
        using TNodeConstPtr = std::shared_ptr<const TNode<T>>;
        using TNodeWeakPtr = std::weak_ptr<TNode<T>>;

        bool hasLeft() const {
            return bool(left);
        }

        bool hasRight() const {
            return bool(right);
        }

        bool hasParent() const {
            // Parent is now of type TNodeWeakPtr 
            return !parent.expired();
        }

        T& getValue() {
            return value;
        }

        const T& getValue() const {
            return value;
        }

        TNodePtr getLeft() {
            return left;
        }

        TNodeConstPtr getLeft() const {
            return left;
        }

        TNodePtr getRight() {
            return right;
        }

        TNodeConstPtr getRight() const {
            return right;
        }

        TNodePtr getParent() {
            // Parent is now of type TNodeWeakPtr 
            return parent.lock();
        }

        TNodeConstPtr getParent() const {
            // Parent is now of type TNodeWeakPtr 
            return parent.lock();
        }

        static TNodePtr createLeaf(T v) {
            // Constructor is private, make_shared does not see it. 
            // If we create custom allocator in the class and call 
            // constructor there, allocate_shared will work
            return std::allocate_shared<TNode>(TNodeAllocator<>(), v);
        }

        // Replaced raw pointers with smart ones to count references correctly
        static TNodePtr fork(T v, TNodePtr left, TNodePtr right) {
            // Same as in createLeaf
            TNodePtr ptr = 
                std::allocate_shared<TNode>(TNodeAllocator<>(),v, left, right);
            setParent(ptr->getLeft(), ptr);
            setParent(ptr->getRight(), ptr);
            return ptr;
        }

        TNodePtr replaceLeft(TNodePtr l) {
            // All pointers created from concrete TNode using this does not know
            // about each other. Enable_shared_from_this counts created pointers
            // and fixes the situation 
            setParent(l, this->shared_from_this());
            setParent(left, nullptr);
            std::swap(l, left);
            return l;
        }

        TNodePtr replaceRight(TNodePtr r) {
            // See replaceLeft
            setParent(r, this->shared_from_this());
            setParent(right, nullptr);
            std::swap(r, right);
            return r;
        }

        TNodePtr replaceRightWithLeaf(T v) {
            return replaceRight(createLeaf(v));
        }

        TNodePtr replaceLeftWithLeaf(T v) {
            return replaceLeft(createLeaf(v));
        }

        TNodePtr removeLeft() {
            return replaceLeft(nullptr);
        }
        TNodePtr removeRight() {
            return replaceRight(nullptr);
        }

    private:
        T value;
        TNodePtr left = nullptr;
        TNodePtr right = nullptr;
        // Required to break circular dependencies to nodes
        TNodeWeakPtr parent;

        // Allocator which is aware of private constructors 
        template<class U = TNode>
        struct TNodeAllocator {
            using value_type = U;
            using pointer = U*;

            TNodeAllocator() noexcept = default;
            template<class W>
            TNodeAllocator(const TNodeAllocator<W>&) {}

            static pointer allocate(std::size_t n) {
                auto mem = ::operator new(n * sizeof(value_type));
                return static_cast<pointer>(mem);
            }

            static void deallocate(pointer p, std::size_t n) {
                auto mem = static_cast<void*>(p);
                ::operator delete(mem);
            }

            template<class... Args>
            static void construct(pointer p, Args&&... args) {
                // Calls replacement new and suitable constructor
                ::new((void *)p) value_type(std::forward<Args>(args)...);
            }

            static void destroy(pointer p) {
                p->~U();
            }
        };

        TNode(T v)
            : value(v)
        {
        }
        TNode(T v, TNodePtr left, TNodePtr right)
            : value(v)
            , left(left)
            , right(right)
        {
        }

        // Replaced raw pointers with smart ones to avoid double free
        static void setParent(TNodePtr node, TNodePtr parent) {
            if (node)
                node->parent = parent;
        }
    };
}
