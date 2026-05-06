#pragma once

#ifdef USING_OPENXR
    #undef USING_OPENXR
#endif
#include "illixr/data_format/normalize.hpp"
#include "illixr/data_format/poses/pose_base.hpp"

#include <eigen3/Eigen/Dense>

namespace ILLIXR {
namespace point {
    //**********************************************************************************
    //  Points
    //**********************************************************************************

    /*
     * struct representing a point in 3-D space. It is essentially an Eigen::Vector with some additional functions
     */
    struct [[maybe_unused]] point : Eigen::Vector3f {
        bool  valid      = false; //!< indicates whether the point contains valid data
        float confidence = 0.;    //!< confidence level of the point's value (0. - 1., with 1. indicating 100% confidence)
        bool  normalized = false; //!< indicates whether this point is in normalized [0., 1.] units

        /*
         * Initial point at the origin
         */
        point()
            : Eigen::Vector3f{0., 0., 0.} { }

        /**
         * Initial point based on the given x, y, and z coordinates
         * @param x The x coordinate in arbitrary units
         * @param y The y coordinate in arbitrary units
         * @param z The z coordinate in arbitrary units, default is 0, indicating a point in 2-D space
         */
        point(const float x, const float y, const float z = 0., bool vld = true, float conf = 0.f, bool norm = false)
            : Eigen::Vector3f(x, y, z)
            , valid{vld}
            , confidence{conf}
            , normalized{norm} { }

        /**
         * Initial point based on the given x, y, and z coordinates
         * @param x The x coordinate in arbitrary units
         * @param y The y coordinate in arbitrary units
         * @param z The z coordinate in arbitrary units
         * @param vld Whether the point contains valid data, default is true
         * @param conf Confidence level of the point's value, default is 0.
         */
        point(const float x, const float y, const float z, bool norm = false, bool vld = true, const float conf = 0.)
            : Eigen::Vector3f{x, y, z}
            , valid{vld}
            , confidence{conf}
            , normalized{norm} { }

        /**
         * Set the coordinates based on the given x, y, and z coordinates
         * @param x The x coordinate in arbitrary units
         * @param y The y coordinate in arbitrary units
         * @param z The z coordinate in arbitrary units, default is 0, indicating a point in 2-D space
         */
        void set(const float x_, const float y_, const float z_ = 0.) {
            x()   = x_;
            y()   = y_;
            z()   = z_;
            valid = true;
        }

        /**
         * Assignment operator
         * @param other The point to copy
         * @return A reference to the updated point
         */
        point& operator=(const Eigen::Vector3f& other) {
            x()        = other.x();
            y()        = other.y();
            z()        = other.z();
            valid      = true;
            confidence = 0.;
            normalized = false;
            return *this;
        }

        /**
         * Assignment operator when dealing with multiplication products
         * @tparam T the type of the left hand side expression
         * @tparam U the type of the right hand side expression
         * @tparam Option
         * @param pr the multiplication product
         * @return a reference to the updated point
         */
        template<typename T, typename U, int Option>
        point& operator=(const Eigen::Product<T, U, Option>& pr) {
            x() = pr.x();
            y() = pr.y();
            z() = pr.z();
            return *this;
        }

        /**
         * Addition operator for adding two points
         * @param other the point to add to this one
         * @return reference to the updated point
         */
        point& operator+=(const Eigen::Vector3f& other) {
            x() += other.x();
            y() += other.y();
            z() += other.z();
            return *this;
        }

        /**
         * Subtraction operator for adding two points
         * @param other the point to subtract from this one
         * @return reference to the updated point
         */
        point& operator-=(const Eigen::Vector3f& other) {
            x() -= other.x();
            y() -= other.y();
            z() -= other.z();
            return *this;
        }

        /**
         * Addition operator between two points the validity flag is an AND of the two flags
         * @param pnt The point to add to this one
         * @return The new point
         */
        point operator+(const point& pnt) const {
            if (normalized != pnt.normalized)
                throw std::runtime_error("Invalid math, incompatible units.");
            point p_out;
            p_out.x()        = x() + pnt.x();
            p_out.y()        = y() + pnt.y();
            p_out.z()        = z() + pnt.z();
            p_out.normalized = normalized;
            p_out.valid      = valid && pnt.valid;
            return p_out;
        }

        /**
         * Subtraction operator between two points the validity flag is an AND of the two
         * flags
         * @param pnt The point to subtract from this one
         * @return The new point
         */
        point operator-(const point& pnt) const {
            if (normalized != pnt.normalized)
                throw std::runtime_error("Invalid math, incompatible units.");
            point p_out;
            p_out.x()        = x() - pnt.x();
            p_out.y()        = y() - pnt.y();
            p_out.z()        = z() - pnt.z();
            p_out.normalized = normalized;
            p_out.valid      = valid && pnt.valid;
            return p_out;
        }

        /**
         * Addition operator between a point and Eigen::Vector
         * @param pnt The point to add to this one
         * @return The new point
         */
        point operator+(const Eigen::Vector3f& pnt) const {
            point p_out;
            p_out.x()        = x() + pnt.x();
            p_out.y()        = y() + pnt.y();
            p_out.z()        = z() + pnt.z();
            p_out.normalized = normalized;
            p_out.valid      = valid;
            return p_out;
        }

        /**
         * Subtraction operator between a point and Eigen::Vector
         * @param pnt The point to subtract from this one
         * @return The new point
         */
        point operator-(const Eigen::Vector3f& pnt) const {
            point p_out;
            p_out.x()        = x() - pnt.x();
            p_out.y()        = y() - pnt.y();
            p_out.z()        = z() - pnt.z();
            p_out.normalized = normalized;
            p_out.valid      = valid;
            return p_out;
        }

        /**
         * Multiplication operator to multiply a point by a constant value
         * @param val The value to multiply by
         * @return The new point
         */
        point operator*(const float val) const {
            point p_out;
            p_out.x() *= val;
            p_out.y() *= val;
            p_out.z() *= val;
            p_out.normalized = normalized;
            p_out.valid      = valid;
            return p_out;
        }

        /**
         * Division operator to divide a point by a constant value
         * @param val The value to divide by
         * @return The new point
         */
        point operator/(const float val) const {
            point p_out;
            p_out.x() /= val;
            p_out.y() /= val;
            p_out.z() /= val;
            p_out.normalized = normalized;
            p_out.valid      = valid;
            return p_out;
        }

        /**
         * Set the coordinates based on the given x, y, and z coordinates
         * @param x The x coordinate in arbitrary units
         * @param y The y coordinate in arbitrary units
         * @param z The z coordinate in arbitrary units
         * @param valid_ Whether the point contains valid data, default is true
         */
        void set(const float x_, const float y_, const float z_, bool norm_, bool valid_ = true) {
            x()        = x_;
            y()        = y_;
            z()        = z_;
            normalized = norm_;
            valid      = valid_;
        }

        /**
         * Set the coordinates based on the given Eigen::Vector
         * @param vec The vector to set the point from
         */
        void set(const Eigen::Vector3f& vec) {
            x() = vec.x();
            y() = vec.y();
            z() = vec.z();
        }
    };

    /*
     * Take the absolute value of the point
     */
    [[maybe_unused]] inline point abs(const point& pnt) {
        return {std::abs(pnt.x()), std::abs(pnt.y()), std::abs(pnt.z()), pnt.normalized, pnt.valid, pnt.confidence};
    }

    /*
     * struct containing a vector of points and overall validity/reliability
     */
    struct [[maybe_unused]] points {
        std::vector<point> points_;            //!< The points
        bool               valid      = false; //!< Indicates the validity of all points, will be true if any point is valid.
        bool               fixed      = false; //!< indicates whther the size of the vector has been set
        bool               normalized = false; //!< indicates whether this point is in normalized [0., 1.] units

        /**
         * Construct a points with an empty list
         */
        explicit points()
            : points_{std::vector<point>()} { }

        /**
         * Construct a points with a list of points with the given size
         * @param size The number of points to initialize
         */
        explicit points(const int size)
            : points_{std::vector<point>(size)}
            , valid{false}
            , fixed{true} { }

        /**
         * Construct a points from a vector of point objects
         * @param points_ The points to move into this object
         * @param valid_ The validity of all points, default is true
         */
        explicit points(std::vector<point>& pnts, bool valid_ = true)
            : valid{valid_} {
            points_.resize(pnts.size());
            if (!points_.empty())
                normalized = points_[0].normalized;
            for (const auto& pnt : points_) {
                if (pnt.normalized != normalized) {
                    std::string msg = "Cannot include ";
                    msg += (pnt.normalized) ? "a normalized" : "an un-normalized";
                    msg += " point in ";
                    msg += (pnt.normalized) ? "a normalized" : "an un-normalized";
                    msg += " grouping";
                    throw std::runtime_error(msg);
                }
            }

            for (size_t i = 0; i < points_.size(); i++)
                points_[i] = pnts[i];
        }

        /**
         * Copy constructor
         * @param points_
         */
        points(const points& pnts)
            : points_(pnts.points_) { }

        /**
         * Copy operator
         * @param other The object to copy into this one
         * @return A reference to the updated points
         */
        points& operator=(const points& other) {
            if (this == &other)
                return *this;
            this->points_.resize(other.points_.size());
            for (size_t i = 0; i < other.points_.size(); i++)
                this->points_[i] = other.points_[i];
            this->normalized  = other.normalized;
            this->valid = other.valid;
            this->fixed = other.fixed;
            return *this;
        }

        /**
         * Indexing operator to get a specific point based on index
         * @param idx The index of the requested point
         * @return A reference to requested point
         */
        point& operator[](const size_t idx) {
            if (fixed)
                return points_.at(idx);
            return points_[idx];
        }

        /**
         * Get the point at the given index
         * @param idx The index of the requested point
         * @return A reference to requested point
         */
        point& at(const size_t idx) {
            return points_.at(idx);
        }

        /**
         * Get a const version of the point at the given index
         * @param idx The index of the requested point
         * @return A const reference to requested point
         */
        [[nodiscard]] const point& at(const size_t idx) const {
            return points_.at(idx);
        }

        /**
         * Get the size of the internal vector
         * @return The number of points stored
         */
        [[nodiscard]] size_t size() const {
            return points_.size();
        }

        /**
         * Multiply all points by a matrix
         * @param ref_frm The matrix to multiply all points by
         */
        [[maybe_unused]] void mult(const Eigen::Matrix3f& ref_frm) {
            for (point& pnt : points_)
                pnt = ref_frm * pnt;
        }

        /**
         * Transform (move) all points by the given pose
         * @param pose The pose to apply to the points
         */
        void transform(const data_format::pose::pose_base& pose) {
            for (point& pnt : points_)
                pnt = (Eigen::Vector3f) ((pose.orientation * pnt) + pose.position);
        }

        /**
         * Enforce point bounds to be valid for an image (e.g. no negative values
         * @param x_lim upper limit of x values
         * @param y_lim upper limit of y values
         * @param z_lim upper limit of z values
         */
        [[maybe_unused]] void enforce_bounds(const float x_lim = -1., const float y_lim = -1, const float z_lim = -1) {
            for (auto& pnt : points_) {
                if (!pnt.valid)
                    continue;
                if (x_lim > 0.) {
                    if (pnt.x() < 0. || pnt.x() >= x_lim) {
                        pnt.valid = false;
                        continue;
                    }
                }
                if (y_lim > 0.) {
                    if (pnt.y() < 0. || pnt.y() >= y_lim) {
                        pnt.valid = false;
                        continue;
                    }
                }
                if (z_lim > 0.) {
                    if (pnt.z() < 0. || pnt.z() >= z_lim) {
                        pnt.valid = false;
                        continue;
                    }
                }
            }
        }

        /**
         * Update the struct validity flag based on the point's flags
         */
        [[maybe_unused]] void check_validity() {
            valid = false;
            for (point& pnt : points_) {
                if (pnt.valid) {
                    valid = true;
                    return;
                }
            }
        }
    };
} // namespace point

/**
 * Normalize a set of points based on the given bounds (all values will be 0. - 1.)
 * @param obj The points to be normalized
 * @param width The x bound
 * @param height The y bound
 * @param depth The z bound
 */
template<>
[[maybe_unused]] inline void normalize<point::points>(point::points& obj, const float width, const float height,
                                                      const float depth) {
    if (obj.normalized) {
        return;
    }
    for (auto& pnt : obj.points_)
        normalize(pnt, width, height, depth);
    obj.normalized = true;
}

/**
 * De-normalize a set of points to coordinates within the given bounds
 * @param obj the points to de-normalize
 * @param width the x bound
 * @param height the y bound
 * @param depth the z bound
 */
template<>
[[maybe_unused]] inline void denormalize<point::points>(point::points& obj, const float width, const float height,
                                                        const float depth) {
    if (!obj.normalized)
        return;
    for (auto& pnt : obj.points_)
        denormalize(pnt, width, height, depth);
    obj.normalized = false;
}

#ifdef ENABLE_OXR
/*
 * This struct is utilized when working with OpenXR. The internal variables are in a basic form since OpenXR uses
 * C, rather than C++ (e.g. points do not inherit from Eigen::Vector)
 */
struct raw_point {
    float x;
    float y;
    float z;
    bool  valid;

    raw_point()
        : x{0.f}
        , y{0.f}
        , z{0.f}
        , valid{false} { }

    [[maybe_unused]] explicit raw_point(const point& pnt)
        : x{pnt.x()}
        , y{pnt.y()}
        , z{pnt.z()}
        , valid{pnt.valid} { }

    void copy(const point& pnt) {
        x     = pnt.x();
        y     = pnt.y();
        z     = pnt.z();
        valid = pnt.valid;
    }

    [[maybe_unused]] void mult(const Eigen::Matrix3f& ref_frm) {
        Eigen::Vector3f vec{x, y, z};
        vec = ref_frm * vec;
        x   = vec.x();
        y   = vec.y();
        z   = vec.z();
    }

    void transform(const pose_data& pose) {
        Eigen::Vector3f vec{x, y, z};
        vec = (Eigen::Vector3f) ((pose.orientation * vec) + pose.position);
        x   = vec.x();
        y   = vec.y();
        z   = vec.z();
    }

    [[maybe_unused]] void de_transform(const pose_data& pose) {
        Eigen::Vector3f vec{x, y, z};
        vec -= pose.position;
        vec = (Eigen::Vector3f) ((pose.orientation.inverse() * vec));
        x   = vec.x();
        y   = vec.y();
        z   = vec.z();
    }
};
#endif

} // namespace ILLIXR
