#!/usr/bin/env python3

import tensorflow as tf

print("TensorFlow version %s" % (tf.__version__))

def show(image):
    for i in range(28):
        for j in range(28):
            if image[i][j] > 0.3:
                print('#', end = '')
            else:
                print('.', end = '')
        print()

digit_file_path = 'digit.h'
digit_content = '''const float mnist_digit[] = {
  %s
};
const int mnist_label = %d;
'''

if __name__ == '__main__':
    mnist = tf.keras.datasets.mnist
    (_, _), (test_images, test_labels) = mnist.load_data()
    index = 0
    shape = 28
    image = test_images[index].astype('float32')/255
    label = test_labels[index]
    print('label: %d' % label)
    #show(image)
    digit_data = (',\n  ').join([ (', ').join([ '%.2f' % image[row][col] for col in range(shape)]) for row in range(shape)])
    digit_file = open(digit_file_path, 'w')
    digit_file.write(digit_content % (digit_data, label))
    digit_file.close()

