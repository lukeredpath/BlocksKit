//
//  NSArray+BlocksKit.m
//  BlocksKit
//

#import "NSArray+BlocksKit.h"

@implementation NSArray (BlocksKit)

- (void)each:(BKSenderBlock)block {
    [self enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        block(obj);
    }];
}

- (id)match:(BKValidationBlock)block {
    NSIndexSet *indexes = [self indexesOfObjectsPassingTest:^BOOL(id obj, NSUInteger idx, BOOL *stop) {
        if (block(obj)) {
            *stop = YES;
            return YES;
        }
        return NO;
    }];
    
    if (indexes.count)
        return [self objectAtIndex:[indexes firstIndex]];
    
    return nil;
}

- (NSArray *)select:(BKValidationBlock)block {
    NSArray *list = [self objectsAtIndexes:[self indexesOfObjectsPassingTest:^BOOL(id obj, NSUInteger idx, BOOL *stop) {
        return (block(obj));
    }]];
    
    if (!list.count)
        return nil;
    
    return list;
}

- (NSArray *)reject:(BKValidationBlock)block {
    NSArray *list = [self objectsAtIndexes:[self indexesOfObjectsPassingTest:^BOOL(id obj, NSUInteger idx, BOOL *stop) {
        return (!block(obj));
    }]];
    
    if (!list.count)
        return nil;
    
    return list;
}

- (NSArray *)map:(BKTransformBlock)block {
    NSMutableArray *result = [NSMutableArray arrayWithCapacity:self.count];
    
    [self enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        id value = block(obj);
        if (!value)
            value = [NSNull null];
        
        [result addObject:value];
    }];
    
    return result;
}

- (id)reduce:(id)initial withBlock:(BKAccumulationBlock)block {
    __block id result = initial;
    
    [self enumerateObjectsUsingBlock:^(id obj, NSUInteger idx, BOOL *stop) {
        result = block(result, obj);
    }];
    
    return result;
}

@end
