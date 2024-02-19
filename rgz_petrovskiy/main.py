from PIL import Image
import numpy as np
from sklearn.cluster import KMeans

# 4. Преобразовать True Color PCX файл в 256-цветный PCX файл.

def main() -> int:
    image = Image.open('сarib_TC.pcx')
    image.show()

    # Преобразование изображения в массив numpy для удобства обработки
    img_array = np.array(image)

    # Преобразование размерности массива для работы с KMeans
    reshaped_array = img_array.reshape(-1, 3)

    # Кластеризация цветов с помощью k-средних на 256 кластеров
    kmeans = KMeans(n_clusters=256, random_state=0).fit(reshaped_array)
    
    # Получение центров кластеров (палитры)
    color_palette = np.array(kmeans.cluster_centers_, dtype=np.uint8)

    # Получение меток кластеров для каждого пикселя
    labels = kmeans.labels_

    # Создание изображения на основе палитры и меток кластеров
    quantized_img = np.zeros_like(reshaped_array)
    for i in range(len(reshaped_array)):
        quantized_img[i] = color_palette[labels[i]]

    # Преобразование массива обратно в изображение
    quantized_img = quantized_img.reshape(img_array.shape)

    # Сохранение и отображение изображения
    result_image = Image.fromarray(quantized_img)
    result_image.save('rgr-result.pcx')
    result_image.show()
    
    return 0

if __name__ == '__main__':
    exit(main())
