___

:o:
__Not implemented__

:ballot_box_with_check:
__Implemented__

:white_check_mark:
__Tested__

:heavy_minus_sign:
__Not needed__

:arrow_down:
__Herited__

:repeat:
__Overload__

:warning:
__C++11__

:no_entry: :no_entry_sign: :x: :negative_squared_cross_mark: :heavy_check_mark: :arrow_down_small: :arrow_heading_down: :repeat_one: :arrows_clockwise: :arrows_counterclockwise:

___

### TODO

__type_trait__
- is_integral
- enable_if (cf. SFINAE)

__algorithm__
- equal and/or lexicographical_compare

__utility__
- std::pair
- std::make_pair

__iterators__
- iterators_traits
- reverse_iterator

___


|                |       Vector       |       Stack        |         Map        |
|----------------|:------------------:|:------------------:|:------------------:|
|  Constructors  |                :o: |                :o: |                :o: |
|  Destructor    |                :o: |                :o: |                :o: |
|  operator=     |                :o: |                :o: |                :o: |
| __Iterators__  |                    |                    |                    |
|  begin         |                :o: |                :o: |                :o: |
|  end           |                :o: |                :o: |                :o: |
|  rbegin        |                :o: |                :o: |                :o: |
|  rend          |                :o: |                :o: |                :o: |
| __Capacity__   |                    |                    |                    |
|  size          |                :o: |                :o: |                :o: |
|  max_size      |                :o: |                :o: |                :o: |
|  resize        |                :o: |                :o: | :heavy_minus_sign: |
|  capacity      |                :o: |                :o: | :heavy_minus_sign: |
|  empty         |                :o: |                :o: |                :o: |
|  reserve       |                :o: |                :o: | :heavy_minus_sign: |
| __Accessors__  |                    |                    |                    |
|  operator[]    |                :o: |                :o: |                :o: |
|  at            |                :o: |                :o: |                :o: |
|  front         |                :o: |                :o: | :heavy_minus_sign: |
|  back          |                :o: |                :o: | :heavy_minus_sign: |
| __Modifiers__  |                    |                    |                    |
|  assign        |                :o: |                :o: | :heavy_minus_sign: |
|  push_front    | :heavy_minus_sign: |                :o: | :heavy_minus_sign: |
|  pop_front     | :heavy_minus_sign: |                :o: | :heavy_minus_sign: |
|  push_back     |                :o: |                :o: | :heavy_minus_sign: |
|  pop_back      |                :o: |                :o: | :heavy_minus_sign: |
|  insert        |                :o: |                :o: |                :o: |
|  erase         |                :o: |                :o: |                :o: |
|  swap          |                :o: |                :o: |                :o: |
|  clear         |                :o: |                :o: |                :o: |
|  resize        | :heavy_minus_sign: |                :o: | :heavy_minus_sign: |
| __Observers__  |                    |                    |                    |
|  key_comp      | :heavy_minus_sign: | :heavy_minus_sign: |                :o: |
|  value_comp    | :heavy_minus_sign: | :heavy_minus_sign: |                :o: |
| __Operations__ |                    |                    |                    |
|  find          | :heavy_minus_sign: | :heavy_minus_sign: |                :o: |
|  count         | :heavy_minus_sign: | :heavy_minus_sign: |                :o: |
|  lower_bound   | :heavy_minus_sign: | :heavy_minus_sign: |                :o: |
|  upper_bound   | :heavy_minus_sign: | :heavy_minus_sign: |                :o: |
|  equal_range   | :heavy_minus_sign: | :heavy_minus_sign: |                :o: |
| __Allocator__  |                    |                    |                    |
| get_allocator  |                :o: |                :o: |                :o: |

___
