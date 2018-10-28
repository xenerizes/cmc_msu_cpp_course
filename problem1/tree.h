#pragma once

#include <memory>

namespace bintree {
    template <typename T>
    struct TNode {
        using TNodePtr = std::shared_ptr<TNode<T>>;
        using TNodeConstPtr = std::shared_ptr<const TNode<T>>;

        bool hasLeft() const {
            return bool(left);
        }

        bool hasRight() const {
            return bool(right);
        }

        bool hasParent() const {
            return bool(parent);
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
            return parent;
        }

        TNodeConstPtr getParent() const {
            return parent;
        }

        static TNodePtr createLeaf(T v) {
            return std::allocate_shared<TNode>(TNodeAllocator<>(),v);
        }

        static TNodePtr fork(T v, TNode* left, TNode* right) {
            TNodePtr ptr = std::allocate_shared<TNode>(TNodeAllocator<>(),v, left, right);
            setParent(ptr->getLeft(), ptr);
            setParent(ptr->getRight(), ptr);
            return ptr;
        }

        TNodePtr replaceLeft(TNodePtr l) {
            setParent(l, TNodePtr(this));
            setParent(left, nullptr);
            std::swap(l, left);
            return l;
        }

        TNodePtr replaceRight(TNodePtr r) {
            setParent(r, TNodePtr(this));
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
        TNodePtr parent = nullptr;

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
        TNode(T v, TNode* left, TNode* right)
            : value(v)
            , left(left)
            , right(right)
        {
        }

        static void setParent(TNodePtr node, TNodePtr parent) {
            if (node)
                node->parent = parent;
        }
    };
}
