//
//  NSArray+BlocksKit.h
//  BlocksKit
//

/** Block extensions for NSArray.
 
 Both inspired by and resembling Smalltalk syntax, these utilities
 allow iteration of an NSArray in a logical and concise way that
 saves quite a bit of boilerplate code for filtering or finding
 objects or an object.
 
 Includes code by the following:

- Robin Lu.       <https://github.com/robin>.      2009. MIT.
- Michael Ash.    <https://github.com/mikeash>.    2010. BSD.
- Aleks Nesterow. <https://github.com/nesterow>.   2010. BSD.
- Zach Waldowski. <https://github.com/zwaldowski>. 2011. MIT.

 @see NSDictionary(BlocksKit)
 @see NSSet(BlocksKit)
 */
@interface NSArray (BlocksKit)

/** Loops through an array and executes the given block with each object.
 
 @param block A single-argument, void-returning code block.
 */
- (void)each:(void (^)(id obj))block;

/** Loops through an array and returns the object matching the block.
 
 @param block A single-argument, BOOL-returning code block.
 @return Returns the object if found, `nil` otherwise.
 @see select:
 */
- (id)match:(BOOL (^)(id obj))block;

/** Loops through an array and returns an array of the objects matching the block.
 
 @param block A single-argument, BOOL-returning code block.
 @return Returns an array of the objects found, `nil` otherwise.
 @see match:
 */
- (NSArray *)select:(BOOL (^)(id obj))block;

/** Call the block once for each object and create an array of the return values.
 
 This is sometimes referred to as a transform, mutating one of each object:
     NSArray *new = [stringArray map:^id(id obj) {
       return [obj stringByAppendingString:@".png"]);
     }];
 
 @warning *Important:* the block can NOT return nil for a given object.  If you
 really have nothing to insert, pass `[NSNull null]` as the return value.
 
 @param block A single-argument, object-returning code block.
 @return Returns an array of the objects returned by the block.
 */
- (NSArray *)map:(id (^)(id obj))block;

/** Arbitrarily accumulate objects using a block.
 
 The concept of this selector is difficult to illustrate in words. The sum can
 be any NSObject, including (but not limited to) an NSString, NSNumber, or NSValue.
 
 For example, you can concentate the strings in an array:
     NSString *concentrated = [stringArray reduce:@"" withBlock:^id(id sum, id obj) {
       return [sum stringByAppendingString:obj];
     }];
 
 You can also do something like summing the lengths of strings in an array:
     NSNumber *sum = [stringArray reduce:nil withBlock:^id(id sum, id obj) {
       return [NSNumber numberWithInteger: [sum integerValue] + obj.length];
     }];
     NSUInteger value = [sum integerValue];

 @param initial The value of the reduction at its start.
 @param block A block that takes the current sum and the next object to return the new sum.
 @return 
 */
- (id)reduce:(id)initial withBlock:(id (^)(id sum, id obj))block;

@end