<template>
    <div class="person">
        <h2>姓名：{{ name }}</h2>
        <h2>年龄：{{ age }}</h2>
        <button @click="changeName">修改名字</button>
        <button @click="changeAge">年龄+1</button>
        <button @click="showTel">点我查看联系方式</button>
    </div>
</template>

<script lang="ts">
import { ref } from 'vue'

export default {
    name: 'Person',
    setup() {
        // 数据
        let name = ref('张三')
        let age = ref(18)
        let tel = '13888888888'

        // 方法
        function changeName() {
            name.value = 'zhangsan'
            console.log(name)
        }
        function changeAge() {
            age.value += 1
            console.log(age)
        }
        function showTel() {
            alert(tel)
        }

        // 返回对象，对象中的：属性、方法等，在模板中均可以直接使用
        return { name, age, tel, changeName, changeAge, showTel }
    }

    // 返回函数，自定义渲染内容
    // setup() {
    //     return () => '你好啊'
    // }
}
</script>

<style scoped></style>
