

#ifndef __ptr_h

template <class type>
class ptr_t {
protected:
  bool _local;
  type *_ptr;

  type *ptr(type*);
public:
  ptr_t<type>();
  bool init(type *);
  ptr_t<type>(type* );
  ~ptr_t<type>();

  type* ptr() const; // {return _ptr;}
  bool local() const;

  ptr_t<type> share() const;
};

extern template class ptr_t<float>;
extern template class ptr_t<void*>;


template <class type>
class array_t : public ptr_t<type> {
protected:
  using ptr_t<type>::_local; //bool _local;
  using ptr_t<type>::_ptr;  //type *_ptr;
  unsigned int _size;

public:
  array_t<type>();
  bool init(unsigned int);
  bool init(type*, unsigned int);
  array_t<type>(unsigned int);
  array_t<type>(type*, unsigned int);

  unsigned int size() const;
  bool copy(const array_t &);
  const type read(unsigned int) const;
  type & operator [] (unsigned int);
};

extern template class array_t<float>;
extern template class array_t<void*>;


template <class type>
class array2d_t : public array_t<type>
{
protected:
  using array_t<type>::_local; //bool _local;
  using array_t<type>::_ptr;   //type *_ptr;
  using array_t<type>::_size;  //unsigned int _size;
  unsigned int _height, _width;

public:
  array2d_t<type>();
  array2d_t<type>(unsigned int, unsigned int);
  array2d_t<type>(type *, unsigned int, unsigned int);
  bool init(unsigned int, unsigned int);
  bool init(type *, unsigned int, unsigned int);

  unsigned int height() const;
  unsigned int width() const;
  bool copy(const array2d_t &);
  const type read(unsigned int, unsigned int) const;
  array_t<type> operator [](unsigned int);

  array_t<type> read_col(unsigned int) const;
  array_t<type *> col(unsigned int);
};

extern template class array2d_t<float>;



template <class type>
class square2d_t : public array2d_t<type>
{
protected:
  using array2d_t<type>::_local;  //[ptr_t] bool _local;
  using array2d_t<type>::_ptr;    //[ptr_t] type *_ptr;
  using array2d_t<type>::_size;   //[array_t] unsigned int _size;
  using array2d_t<type>::_height; //[array2d_t] unsigned int _height;
  using array2d_t<type>::_width;  //[array2d_t] unsigned int _width;

public:
  square2d_t<type>();
  bool init(unsigned int);
  bool init(type*, unsigned int);
  square2d_t<type>(unsigned int);
  square2d_t<type>(type*, unsigned int);
};

extern template class square2d_t<float>;




template <class scalar> 
class vector_t : public array_t<scalar>
{
protected:
  using array_t<scalar>::_local; //bool _local;
  using array_t<scalar>::_ptr;  //type *_ptr;
  using array_t<scalar>::_size; //unsigned int;


    vector_t<scalar> op_add(vector_t<scalar>, const vector_t<scalar>);
    vector_t<scalar> op_sub(vector_t<scalar>, const vector_t<scalar>);

    vector_t<scalar> op_mul(vector_t<scalar>, scalar);
    vector_t<scalar> op_div(vector_t<scalar>, scalar);

    vector_t<scalar> op_dot(vector_t<scalar>, const vector_t<scalar>);
    vector_t<scalar> op_bar(vector_t<scalar>, const vector_t<scalar>);

    bool op_equ(const vector_t<scalar>, const vector_t<scalar>) const;
    bool op_neq(const vector_t<scalar>, const vector_t<scalar>) const;

    void op_nul();
    void op_neg();

public:

  static bool op_dotw_addb(scalar &, const vector_t<scalar> &, const vector_t<scalar> &, const scalar &);

  vector_t<scalar>();
  bool init(unsigned int);
  bool init(scalar*, unsigned int);
  vector_t<scalar>(unsigned int);
  vector_t<scalar>(scalar*, unsigned int);

  vector_t<scalar> operator += ( const vector_t<scalar> & );
  vector_t<scalar> operator -= ( const vector_t<scalar> & );

  vector_t<scalar> operator *= ( const scalar & );
  vector_t<scalar> operator /= ( const scalar & );

  vector_t<scalar> operator *= ( const vector_t<scalar> & );
  vector_t<scalar> operator /= ( const vector_t<scalar> & );

  bool operator == ( const vector_t<scalar> & ) const;
  bool operator != ( const vector_t<scalar> & ) const;
};

extern template class vector_t<float>;


template <class scalar>
class matrix_t : public array2d_t<scalar>
{
protected:
  using array2d_t<scalar>::_local;  //[ptr_t] bool _local;
  using array2d_t<scalar>::_ptr;    //[ptr_t] scalar *_ptr;
  using array2d_t<scalar>::_size;   //[array_t] unsigned int _size;
  using array2d_t<scalar>::_height; //[array2d_t] unsigned int _height;
  using array2d_t<scalar>::_width;  //[array2d_t] unsigned int _width;

    matrix_t<scalar> op_add(matrix_t<scalar>, const matrix_t<scalar>);
    matrix_t<scalar> op_sub(matrix_t<scalar>, const matrix_t<scalar>);

    matrix_t<scalar> op_mul(matrix_t<scalar>, scalar);
    matrix_t<scalar> op_div(matrix_t<scalar>, scalar);

    matrix_t<scalar> op_dot(matrix_t<scalar>, const matrix_t<scalar>);
    matrix_t<scalar> op_bar(matrix_t<scalar>, const matrix_t<scalar>);


    bool op_equ(const matrix_t<scalar>, const matrix_t<scalar>) const;
    bool op_neq(const matrix_t<scalar>, const matrix_t<scalar>) const;

    void op_nul();
    void op_neg();

public:
  matrix_t<scalar>();
  bool init(unsigned int, unsigned int);
  bool init(scalar*, unsigned int, unsigned int);
  matrix_t<scalar>(unsigned int, unsigned int);
  matrix_t<scalar>(scalar*, unsigned int, unsigned int);

  matrix_t<scalar> operator += ( const matrix_t<scalar> & );
  matrix_t<scalar> operator -= ( const matrix_t<scalar> & );

  matrix_t<scalar> operator *= ( const scalar & );
  matrix_t<scalar> operator /= ( const scalar & );

  matrix_t<scalar> operator *= ( const matrix_t<scalar> & );
  matrix_t<scalar> operator /= ( const matrix_t<scalar> & );

  static bool op_mult(matrix_t<scalar> &, const matrix_t<scalar> &, const matrix_t<scalar> &);


  bool operator == ( const matrix_t<scalar> & ) const;
  bool operator != ( const matrix_t<scalar> & ) const;
};

extern template class matrix_t<float>;



template <class scalar>
class complex_t
{
protected:

    static complex_t<scalar> _stack;

    void op_add(complex_t<scalar> &, const complex_t<scalar> &) const;
    void op_sub(complex_t<scalar> &, const complex_t<scalar> &) const;

    void op_mul(complex_t<scalar> &, const scalar &) const;
    void op_div(complex_t<scalar> &, const scalar &) const;

    void op_mul(complex_t<scalar> &, const complex_t<scalar> &) const;
    void op_div(complex_t<scalar> &, const complex_t<scalar> &) const;


public:
  scalar re, im;

    complex_t<scalar>();
    complex_t<scalar>(scalar);
    complex_t<scalar>(scalar, scalar);
    complex_t<scalar>(const complex_t<scalar> &);

    scalar norm2() const;

    complex_t<scalar> operator + ( const complex_t<scalar> ) const;
    complex_t<scalar> operator - ( const complex_t<scalar> ) const;

    complex_t<scalar> operator * ( const scalar ) const;
    complex_t<scalar> operator / ( const scalar ) const;

    complex_t<scalar> operator * ( const complex_t<scalar> ) const;
    complex_t<scalar> operator / ( const complex_t<scalar> ) const;

    complex_t<scalar> & operator += ( const complex_t<scalar> );
    complex_t<scalar> & operator -= ( const complex_t<scalar> );

    complex_t<scalar> & operator *= ( const scalar );
    complex_t<scalar> & operator /= ( const scalar );

    complex_t<scalar> & operator *= ( const complex_t<scalar> );
    complex_t<scalar> & operator /= ( const complex_t<scalar> );

    bool operator == ( const complex_t<scalar> ) const; 
    bool operator != ( const complex_t<scalar> ) const;
    bool operator < ( const complex_t<scalar> ) const; // comparison in norm2;
    bool operator > ( const complex_t<scalar> ) const; //
    bool operator <= ( const complex_t<scalar> ) const; //
    bool operator >= ( const complex_t<scalar> ) const; //

    complex_t<scalar> operator ~ () const; // conjugate
    complex_t<scalar> operator - () const; // negation
    complex_t<scalar> inv() const;

    vector_t<scalar> vector_cast();    


    class polar_t {

    public:
      scalar r, theta;

    };
};

extern template class complex_t<float>;


template <class scalar>
class quaternion_t
{
protected:
    static quaternion_t<scalar> _stack, _op_stack;


    void op_add(quaternion_t<scalar> &, const quaternion_t<scalar> &) const;
    void op_sub(quaternion_t<scalar> &, const quaternion_t<scalar> &) const;

    void op_add(quaternion_t<scalar> &, const complex_t<scalar> &) const;
    void op_sub(quaternion_t<scalar> &, const complex_t<scalar> &) const;

    void op_add(quaternion_t<scalar> &, const scalar &) const;
    void op_sub(quaternion_t<scalar> &, const scalar &) const;


    void op_mul(quaternion_t<scalar> &, const scalar &) const;
    void op_div(quaternion_t<scalar> &, const scalar &) const;

    void op_mul(quaternion_t<scalar> &, const complex_t<scalar> &) const;
    void op_div(quaternion_t<scalar> &, const complex_t<scalar> &) const;

    void op_mul(quaternion_t<scalar> &, const quaternion_t<scalar> &) const;
    void op_div(quaternion_t<scalar> &, const quaternion_t<scalar> &) const;
  
public:
  scalar w, x, y, z; // uses quaternion for the accessors.  

  quaternion_t<scalar>();
  quaternion_t<scalar>(complex_t< complex_t<scalar> >); // acknowledge nested complex numbers
  quaternion_t<scalar>(complex_t<scalar>, complex_t<scalar>);
  quaternion_t<scalar>(scalar, scalar, scalar, scalar);
  quaternion_t<scalar>(const quaternion_t<scalar> &);
  
  scalar norm2() const;
  
    quaternion_t<scalar> operator ~ () const; // conjugate
    quaternion_t<scalar> operator - () const; // negation
    quaternion_t<scalar> inv() const;

    quaternion_t<scalar> operator + (const quaternion_t<scalar>) const;
    quaternion_t<scalar> operator - (const quaternion_t<scalar>) const;

    quaternion_t<scalar> & operator += (const quaternion_t<scalar>);
    quaternion_t<scalar> & operator -= (const quaternion_t<scalar>);

    quaternion_t<scalar> operator + (const complex_t<scalar>) const;
    quaternion_t<scalar> operator - (const complex_t<scalar>) const;

    quaternion_t<scalar> & operator += (const complex_t<scalar>);
    quaternion_t<scalar> & operator -= (const complex_t<scalar>);

    quaternion_t<scalar> operator + (const scalar) const;
    quaternion_t<scalar> operator - (const scalar) const;

    quaternion_t<scalar> & operator += (const scalar);
    quaternion_t<scalar> & operator -= (const scalar);

    quaternion_t<scalar> operator * (const scalar) const;
    quaternion_t<scalar> operator / (const scalar) const;

    quaternion_t<scalar> & operator *= (const scalar);
    quaternion_t<scalar> & operator /= (const scalar);

    quaternion_t<scalar> operator * (const complex_t<scalar>) const;
    quaternion_t<scalar> operator / (const complex_t<scalar>) const;

    quaternion_t<scalar> & operator *= (const complex_t<scalar>);
    quaternion_t<scalar> & operator /= (const complex_t<scalar>);

    quaternion_t<scalar> operator * (const quaternion_t<scalar>) const;
    quaternion_t<scalar> operator / (const quaternion_t<scalar>) const;

    quaternion_t<scalar> & operator *= (const quaternion_t<scalar>);
    quaternion_t<scalar> & operator /= (const quaternion_t<scalar>);


    bool operator == (const quaternion_t<scalar>) const;
    bool operator != (const quaternion_t<scalar>) const;
    bool operator < (const quaternion_t<scalar>) const;// comparison in norm2;
    bool operator > (const quaternion_t<scalar>) const;//
    bool operator <= (const quaternion_t<scalar>) const;//
    bool operator >= (const quaternion_t<scalar>) const;//

    vector_t<scalar> vector_cast();
    complex_t< complex_t<scalar> > & complex_cast();
};

extern template class quaternion_t<float>;


template <class scalar>
class hamiltonian_t {
protected:
  static hamiltonian_t<scalar> _stack, _op_stack;

    void op_add(hamiltonian_t<scalar> &, const hamiltonian_t<scalar> &) const;
    void op_sub(hamiltonian_t<scalar> &, const hamiltonian_t<scalar> &) const;
    void op_dot(hamiltonian_t<scalar> &, const hamiltonian_t<scalar> &) const;

    void op_mul(hamiltonian_t<scalar> &, const scalar &) const;
    void op_div(hamiltonian_t<scalar> &, const scalar &) const;

    void op_mul(hamiltonian_t<scalar> &, const hamiltonian_t<scalar> &) const;
    void op_div(hamiltonian_t<scalar> &, const hamiltonian_t<scalar> &) const;

public:
  scalar x, y, z;


    hamiltonian_t<scalar>();
    hamiltonian_t<scalar>(scalar, scalar, scalar);
    hamiltonian_t<scalar>(const hamiltonian_t<scalar> &);

    scalar norm2() const;

    hamiltonian_t<scalar> operator - () const;
    hamiltonian_t<scalar> inv() const;

    hamiltonian_t<scalar> operator + (const hamiltonian_t<scalar>) const;
    hamiltonian_t<scalar> operator - (const hamiltonian_t<scalar>) const;
    hamiltonian_t<scalar> stack_dot (const hamiltonian_t<scalar>) const;

    hamiltonian_t<scalar> operator * (const scalar) const;
    hamiltonian_t<scalar> operator / (const scalar) const;

    hamiltonian_t<scalar> operator * (const hamiltonian_t<scalar>) const;
    hamiltonian_t<scalar> operator / (const hamiltonian_t<scalar>) const;

    hamiltonian_t<scalar> & operator += (const hamiltonian_t<scalar>);
    hamiltonian_t<scalar> & operator -= (const hamiltonian_t<scalar>);
    hamiltonian_t<scalar> & dot_equals (const hamiltonian_t<scalar>);

    hamiltonian_t<scalar> & operator *= (const scalar);
    hamiltonian_t<scalar> & operator /= (const scalar);

    hamiltonian_t<scalar> & operator *= (const hamiltonian_t<scalar>);
    hamiltonian_t<scalar> & operator /= (const hamiltonian_t<scalar>);


    bool operator == (const hamiltonian_t<scalar>) const; 
    bool operator != (const hamiltonian_t<scalar>) const;
    bool operator < (const hamiltonian_t<scalar>) const; // comparison in norm2;
    bool operator > (const hamiltonian_t<scalar>) const; //
    bool operator <= (const hamiltonian_t<scalar>) const; //
    bool operator >= (const hamiltonian_t<scalar>) const; //

  vector_t<scalar> vector_cast();
  quaternion_t<scalar> quaternion_cast();
  quaternion_t<scalar> quaternion_cast(scalar _re);


};

extern template class hamiltonian_t<float>;

extern template class ptr_t<complex_t<float>>;
extern template class array_t<complex_t<float>>;
extern template class array2d_t<complex_t<float>>;
extern template class vector_t<complex_t<float>>;
extern template class matrix_t<complex_t<float>>;

extern template class ptr_t<quaternion_t<float>>;
extern template class array_t<quaternion_t<float>>;
extern template class array2d_t<quaternion_t<float>>;
extern template class vector_t<quaternion_t<float>>;
extern template class matrix_t<quaternion_t<float>>;

extern template class ptr_t<hamiltonian_t<float>>;
extern template class array_t<hamiltonian_t<float>>;
extern template class array2d_t<hamiltonian_t<float>>;
extern template class vector_t<hamiltonian_t<float>>;
extern template class matrix_t<hamiltonian_t<float>>;

extern template class ptr_t<matrix_t<float>>;
extern template class ptr_t<matrix_t<complex_t<float>>>;
extern template class ptr_t<matrix_t<quaternion_t<float>>>;
extern template class ptr_t<matrix_t<hamiltonian_t<float>>>;

extern template class array_t<matrix_t<float>>;
extern template class array_t<matrix_t<complex_t<float>>>;
extern template class array_t<matrix_t<quaternion_t<float>>>;
extern template class array_t<matrix_t<hamiltonian_t<float>>>;

#define __ptr_h
#endif



