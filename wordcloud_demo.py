import wordcloud
import jieba
from PIL import Image
import numpy as np

mask = np.array(Image.open("mask.png"))
#c = wordcloud.WordCloud()
c = wordcloud.WordCloud(width=1000, height=800, font_path="/usr/share/fonts/truetype/wqy-microhei.ttc", mask=mask)

txt = '康 建 包 娜 娜 陈 珍 丁 雪 杨 董 乐 董 令 彩 董 亦 飞 方 锐 范 丽 凤 封 宁 高 媛 弓 琰 郭 成 凯 韩 文 娟 侯 建 黄 思 远 蒋 莹 冰 解 知 杭 李 伋 刘 昌 松 刘 航 欣 刘 腾 宇 芦 正 吕 鹏 秦 银 萍 綦 思 源 阮 乐 成 史 天 水 苏 垚 王 春 杰 王 华 卿 王 磊 王 威 吴 沣 武 文 博 夏 文 华 袁 满 余 旭 东 于 雪 于 雪 莉 翟 中 洋 赵 明 天 赵 顺 意 赵 秭 杭 郑 卿 郑 子 隆 朱 秋 炎 朱 松 纯 朱 毅 鑫'
#txt = "kang jian bao na na chen zhen ding xue yang dong le ling cai dong dong yi fei fang rui li feng fan feng ning gao yuan gong yan guo cheng kai han wen juan hou jian si yuan huang jiang ying bing xie zhi hang li ji liu chang song liu hang xin liu teng yu lu zheng lv peng qin yin ping si yuan qi ruan le cheng shi tian shui su yao wang chun jie wang hua qing wang lei wang wei wu feng wu wen bo xia wen hua yuan man yu xu dong yu xue yu xue li zhai zhong yang ming tian zhao zhao shun yi zhao zi hang zheng qing zi long zheng zhu qiu yan sun chun zhu yi xin zhu"
c.generate(" ".join(jieba.lcut(txt)))
c.to_file("visual_result.png") 



